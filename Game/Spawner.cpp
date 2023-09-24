#include "Spawner.h"

#include "Loner.h"
#include "Rusher.h"
#include "Drone.h"
#include "StoneAster.h"
#include "MetalAster.h"

#include "WeaponPowerUp.h"
#include "ShieldPowerUp.h"

#include "Companion.h"

#include <stdio.h>   
#include <stdlib.h>  
#include <time.h>  

Spawner::Spawner(){
	
}
Spawner::~Spawner()
{
	//não é necessario deletar entidades criadas aqui pois são deletadas no pelo nivel
	playerReference = nullptr;
}


void Spawner::Init()
{
	Entity::Init();
	srand(static_cast<unsigned int>(time(NULL)));
	windowHeight = GameEngine::GetInstance()->GameWindowHeight();
	windowWidth = GameEngine::GetInstance()->GameWindowWidht();
}

void Spawner::Update()
{
	Entity::Update();

	//std::cout << "level enemies: " << levelEnemies.size() <<"\n";

	SpawnLoner();
	SpawnRusher();
	SpawnDrone();

	SpawnStoneAsteroid(ChooseAsterSize());
	SpawnMetalAsteroid(ChooseAsterSize());
	
	SpawnShieldPowerUp();
	SpawnWeaponPowerUp();
	SpawnCompanion();

}

void Spawner::SpawnLoner()
{
	/// <Spawn Loner>
	lonerDeltaTime += GameEngine::GetInstance()->GetDeltatime();

	if (lonerDeltaTime > lonerSpawnRate)
	{
		std::pair<float, float> pos = SpawnPosAlongX(true, true);
		levelEnemies.push_back((new Loner(pos.first, pos.second, this)));
		lonerDeltaTime = 0;
	}
}

void Spawner::SpawnRusher()
{
	rusherDeltaTime += GameEngine::GetInstance()->GetDeltatime();

	if (rusherDeltaTime > rusherSpawnRate)
	{
		std::pair<float, float> pos = SpawnPosAlongY(true, true);
		levelEnemies.push_back((new Rusher(pos.first, pos.second, this)));
		rusherDeltaTime = 0;
	}
}

void Spawner::SpawnDrone()
{
	droneDeltaTime += GameEngine::GetInstance()->GetDeltatime();

	if (droneDeltaTime > droneSpawnRate)
	{
		if (!spawningDronePack)
		{
			std::pair<float, float> pos = SpawnPosAlongY(true, true);
			dronePackSpawnPoint.second = pos.second;
			dronePackSpawnPoint.first = pos.first;
			droneSpawnRate = droneSpawnRateShort;
			spawningDronePack = true;
		}

		levelEnemies.push_back(new Drone (dronePackSpawnPoint.first, dronePackSpawnPoint.second, this));
		++droneCount;
		droneDeltaTime = 0;

		if (droneCount >= dronePackNumber)
		{
			droneSpawnRate = droneSpawnRateLong;
			spawningDronePack = false;
			droneCount = 0;

		}
	}
}

void Spawner::SpawnStoneAsteroid(int size)
{
	stoneAsterDeltaTime += GameEngine::GetInstance()->GetDeltatime();

	if (stoneAsterDeltaTime > stoneAsterSpawnRate)
	{
		float iSecret = static_cast<float>(rand() % (windowHeight + 1));
		levelEnemies.push_back(new StoneAster(size, static_cast<float>(windowWidth), iSecret, this));
		stoneAsterDeltaTime = 0;
	}
}

void Spawner::SpawnMetalAsteroid(int size)
{
	metalAsterDeltaTime += GameEngine::GetInstance()->GetDeltatime();

	if (metalAsterDeltaTime > metalAsterSpawnRate)
	{
		float iSecret = static_cast<float>(rand() % (windowHeight + 1));
		levelEnemies.push_back(new MetalAster(size, static_cast<float>(windowWidth), iSecret, this));
		metalAsterDeltaTime = 0;
	}
}

void Spawner::SpawnShieldPowerUp()
{
	shieldPUDeltaTime += GameEngine::GetInstance()->GetDeltatime();

	if (shieldPUDeltaTime > shieldPUSpawnRate)
	{
		float iSecret = static_cast<float>(rand() % (windowHeight + 1));
		levelPowerUps.push_back(new ShieldPowerUp((windowWidth), iSecret, this));
		shieldPUDeltaTime = 0;
	}
}

void Spawner::SpawnWeaponPowerUp()
{
	weaponPUDeltaTime += GameEngine::GetInstance()->GetDeltatime();

	if (weaponPUDeltaTime > weaponPUSpawnRate)
	{
		float iSecret = static_cast<float>(rand() % (windowHeight + 1));
		levelPowerUps.push_back(new WeaponPowerUp((windowWidth), iSecret, this));
		weaponPUDeltaTime = 0;
	}
}

void Spawner::SpawnCompanion()
{
	if (needCompanion)
	{
		companionDeltaTime += GameEngine::GetInstance()->GetDeltatime();
	}

	if (companionDeltaTime > companionSpawnRate)
	{
		float iSecret = static_cast<float>(rand() % (windowHeight + 1));
		levelPowerUps.push_back(new Companion((windowWidth), iSecret, this));
		companionDeltaTime = 0;
	}
}

void Spawner::RemoveEnemy(Enemy* enemy)
{
	for (int i = 0; i < levelEnemies.size(); ++i)
	{
		if (levelEnemies.at(i) == enemy)
		{
			levelEnemies.erase(levelEnemies.begin() + i);
			break;
		}
	}
}

void Spawner::RemovePowerUp(Entity* powerUp)
{
	for (int i = 0; i < levelPowerUps.size(); ++i)
	{
		if (levelPowerUps.at(i) == powerUp)
		{
			levelPowerUps.erase(levelPowerUps.begin() + i);
			break;
		}
	}
}

void Spawner::SetPlayerReference(Spaceship* player)
{
	playerReference = player;
}

Vector2D Spawner::GetPlayerPosition()
{
	return (playerReference->GetComponent<Transform>().myPosition);
}


std::pair<float, float> Spawner::SpawnPosAlongX(bool shouldSpawnUp, bool shouldSpawnDown)
{
	std::pair<float, float> pos;

	pos.first = static_cast<float>(rand() % (windowWidth + 1));
	pos.second = 0.0f;

	if (shouldSpawnUp && shouldSpawnDown)
	{
		int spawnDir = rand() % 2;
		
		if (spawnDir == 1)
		{
			pos.second = static_cast<float>(windowHeight);
		}
	}
	if (shouldSpawnDown)
	{
		pos.second = static_cast<float>(windowHeight);
	}

	return pos;
}

std::pair<float, float> Spawner::SpawnPosAlongY(bool shouldSpawnRight, bool shouldSpawnLeft)
{
	std::pair<float, float> pos;

	pos.second = static_cast<float>(rand() % (windowHeight + 1));
	pos.first = 0.0f;

	if (shouldSpawnRight && shouldSpawnLeft)
	{
		int spawnDir = rand() % 2;
		 if (spawnDir == 1)
		{
			pos.first = static_cast<float>(windowWidth);
		}
	}
	else if (shouldSpawnRight)
	{
		pos.first = static_cast<float>(windowWidth);
	}

	return pos;
}

void Spawner::CompanionNecessity(bool companionNecessity)
{
	needCompanion = companionNecessity;
}

int Spawner::ChooseAsterSize() 
{
	int size{};
	int iSecret = (rand() % 3) + 1;
	
	switch (iSecret)
	{
	case 1:
		size = 96;
		break;
	case 2:
		size = 64;
		break;
	case 3:
		size = 32;
		break;
	default:
		break;
	}

	return size;

}
