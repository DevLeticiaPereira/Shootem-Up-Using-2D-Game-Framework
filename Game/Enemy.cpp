#include "Enemy.h"
#include "Spaceship.h"
#include "Companion.h"
#include "Spawner.h"
#include "UIManager.h"

Enemy::~Enemy(){}

Enemy::Enemy()
{
	die = new Animation("enemydie", "assets/explode64.bmp", 2, 5, 2, 5, 1, 1, 15, false, 2, false, true, true);
}

void Enemy::Update()
{
	Entity::Update();
	

	if (health <= 0)
	{
		if (!GetComponent<Animator>().AnimationIsPlaying())
		{
			mySpawner->RemoveEnemy(this);
			Destroy();
		}

		GetComponent<Collider>().SetBullet(false);
	}
	else 
	{
		if (GetComponent<Transform>().myPosition.X > ((GameEngine::GetInstance()->GameWindowWidht()) + 64) ||
			GetComponent<Transform>().myPosition.X < -64)
		{
			mySpawner->RemoveEnemy(this);
			Destroy();
		}

		if (GetComponent<Transform>().myPosition.Y > ((GameEngine::GetInstance()->GameWindowHeight()) + 64) ||
			GetComponent<Transform>().myPosition.Y < -64)
		{
			mySpawner->RemoveEnemy(this);
			Destroy();
		}
	}

}

void Enemy::Init()
{
	Entity::Init();
	if (HasComponent<Animator>())
		GetComponent<Animator>().AddAnimation("enemydie", die);
}

void Enemy::WasHit(Entity* collidedObject)
{
	if (collidedObject->GetComponent<Collider>().GetId() == "Spaceship")
	{
		Spaceship* currentPlayer = static_cast<Spaceship*>(collidedObject);
		currentPlayer->ApplyDamage((currentPlayer->maxHealth) / 3);
		currentPlayer->ChangeBulletLevel(false);
		ApplyDamage(health, collidedObject);
	}

	if (collidedObject->GetComponent<Collider>().GetId() == "Companion")
	{
		Companion* playerCompanion = static_cast<Companion*>(collidedObject);

		if (playerCompanion->IsTaken())
		{
			playerCompanion->ApplyDamage((playerCompanion->maxHealth) / 3);
			playerCompanion->ChangeBulletLevel(false);
			ApplyDamage(health, collidedObject);
		}
	}

}

void Enemy::ApplyDamage(float damage, Entity* collidedObject)
{
	if (canReceiveDamage)
	{
		health -= damage;
	}
		
	if (health <= 0)
	{
		if (collidedObject->GetComponent<Collider>().GetId() == "Bullet")
		{
			UIManager::GetInstance()->UpdateScore(score);
			UIManager::GetInstance()->ScoreUi(GetComponent<Transform>().myPosition, std::to_string(GetScore()));
		}
		
		if (HasComponent<Animator>())
			GetComponent<Animator>().PlayFromStart("enemydie", false, true);	
	}
}
