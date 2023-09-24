#include "Companion.h"
#include "Spaceship.h"
#include "Bullet.h"
#include "UIManager.h"

Companion::Companion(float posX, float posY, Spawner* spawner)
{
	AddComponent<Animator>();
	maxHealth = 50;
	health = maxHealth;
	bulletLevel = 1;
	bulletMinLevel = 1;
	bulletMaxLevel = 3;
	spawnPosX = posX;
	spawnPosY = posY;
	companionSpawner = spawner;
	companionIdle = new Animation("companionIdle", "assets/clone.bmp", 5, 4, 4, 4, 1, 1, 10, false, 3, true, true, true);

	GetComponent<Transform>().myRotation = -90.0f;
	GetComponent<Animator>().AddAnimation("companionIdle", companionIdle);
}

Companion::~Companion()
{
	//Entity::~Entity();
}

Spawner* Companion::GetSpawner()
{
	return companionSpawner;
}

void Companion::Init()
{
	Entity::Init();

	GetComponent<Transform>().myPosition.X = spawnPosX;
	GetComponent<Transform>().myPosition.Y = spawnPosY;

	GetComponent<Animator>().PlayFromStart("companionIdle", true, true);

	float colliderHeight = static_cast<float>(GetComponent<Animator>().GetAnimationByName("companionIdle")->frameHeight) + 10;
	float colliderWidth = static_cast<float>(GetComponent<Animator>().GetAnimationByName("companionIdle")->frameWidth) + 10;

	AddComponent<Collider>().AddAttributes("Companion", this, Collider::BodyType::dynamicBody,
		GetComponent<Transform>().myPosition.X,
		GetComponent<Transform>().myPosition.Y,
		colliderWidth, colliderHeight, true, 0.0f);
}

void Companion::Update()
{
	Entity::Update();

	bulletDeltaTime += GameEngine::GetInstance()->GetDeltatime();

	if (!isTaken)
	{
		GetComponent<Transform>().myPosition.X += moveSpeed * GameEngine::GetInstance()->GetDeltatime();

		float compPosX = GetComponent<Transform>().myPosition.X;
		float compPosY = GetComponent<Transform>().myPosition.Y;

		Vector2D colliderVelocity = (compPosX, compPosY);

		GetComponent<Collider>().SetVelocity(colliderVelocity);
		GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X, GetComponent<Transform>().myPosition.Y);
	}
	else
	{
		float compPosX = currentPlayer->GetComponent<Transform>().myPosition.X + displacementY;
		float compPosY = currentPlayer->GetComponent<Transform>().myPosition.Y + displacementX;

		GetComponent<Transform>().myPosition.X = compPosX;
		GetComponent<Transform>().myPosition.Y = compPosY;

		Vector2D colliderVelocity = (compPosX, compPosY);

		GetComponent<Collider>().SetVelocity(colliderVelocity);

		GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X, GetComponent<Transform>().myPosition.Y);	
	}
}

void Companion::Attack()
{
	if (bulletDeltaTime > bulletCoolDown)
	{
		Bullet* bullet = new Bullet(GetComponent<Transform>().myPosition.X + 55, GetComponent<Transform>().myPosition.Y, bulletLevel);
		bulletDeltaTime = 0;
	}
}

void Companion::ApplyShield(int shieldValue)
{
	if (health < maxHealth)
	{
		health += shieldValue;
		UIManager::GetInstance()->ScoreUi(GetComponent<Transform>().myPosition, "shield up");
	}
	if (health > maxHealth)
	{
		health = maxHealth;
	}
}

void Companion::ApplyDamage(int damageReceived)
{
	health -= damageReceived;

	if (health <= 0 && isTaken)
	{
		//std::cout << "posx: " << displacementX << "posy: " << displacementY << std::endl;
		currentPlayer->RemoveCompanion(static_cast<float>(displacementX), static_cast<float>(displacementY), this);
	}
}

void Companion::SetDisplacement(Vector2D displacementVector)
{
	displacementX = static_cast<int>(displacementVector.X);
	displacementY = static_cast<int>(displacementVector.Y);
}

void Companion::ChangeBulletLevel(bool willIncrease)
{
	if (willIncrease)
	{
		if (bulletLevel != bulletMaxLevel)
		{
			++bulletLevel;
			UIManager::GetInstance()->ScoreUi(GetComponent<Transform>().myPosition, "weapon up");
		}
	}
	else if (!willIncrease)
	{
		if (bulletLevel != bulletMinLevel)
		{
			--bulletLevel;
		}
	}
}

void Companion::TakeCompanion(bool willTake)
{
	isTaken = willTake;
}

void Companion::SetPlayerReference(Spaceship* player)
{
	currentPlayer = player;
}

bool Companion::IsTaken()
{
	return isTaken;
}
