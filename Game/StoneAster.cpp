#include "StoneAster.h"
#include "Spawner.h"

#include <stdio.h>   
#include <stdlib.h>  
#include <time.h>  

StoneAster::StoneAster(int size, float posX, float posY, Spawner* spawner)
{
	mySpawner = spawner;
	spawnPosX = posX;
	spawnPosY = posY;
	asterSize = size;

	AddComponent<Animator>();

	switch (size)
	{
		case 96:
		{
			idle = new Animation("idleStone96", "assets/SAster96.bmp", 5, 5, 5, 5, 1, 1, 10, false, 2, true, true, true);
			die = new Animation("enemydie64", "assets/explode64.bmp", 2, 5, 2, 5, 1, 1, 15, false, 2, false, true, true);
			moveSpeedX = 40;
			score = 75;
			break;
		}
		case 64:
		{
			idle = new Animation("idleStone64", "assets/SAster64.bmp", 3, 8, 3, 8, 1, 1, 10, false, 2, true, true, true);
			die = new Animation("enemydie32", "assets/explode32.bmp", 2, 5, 2, 5, 1, 1, 30, false, 2, false, true, true);
			moveSpeedX = 55;
			score = 50;
			break;
		}
		case 32:
		{
			idle = new Animation("idleStone32", "assets/SAster32.bmp", 2, 8, 2, 8, 1, 1, 8, false, 2, true, true, true);
			die = new Animation("enemydie16", "assets/explode16.bmp", 2, 5, 2, 5, 1, 1, 30, false, 2, false, true, true);
			moveSpeedX = 75;
			score = 25;
			break;
		}
		default:
		break;
	}

	GetComponent<Animator>().AddAnimation("idle", idle);

	health = 10;
}

StoneAster::~StoneAster()
{
}

void StoneAster::Init()
{
	Enemy::Init();

	float colliderHeight = static_cast<float>(GetComponent<Animator>().GetAnimationByName("idle")->frameHeight);
	float colliderWidth = static_cast<float>(GetComponent<Animator>().GetAnimationByName("idle")->frameWidth);

	AddComponent<Collider>().AddAttributes("Enemy", this, Collider::BodyType::dynamicBody,
		GetComponent<Transform>().myPosition.X,
		GetComponent<Transform>().myPosition.Y,
		colliderWidth, colliderHeight, true, 0.0f);

	GetComponent<Transform>().myPosition.X = spawnPosX;
	GetComponent<Transform>().myPosition.Y = spawnPosY;

	moveSpeedY = static_cast<float>((rand() % 16));
	int sighn = rand() % (2);
	if (sighn != 1)
	{
		moveSpeedY *= -1;
	}
}

void StoneAster::Update()
{
	Enemy::Update();

	if (health <= 0 && !hasCracked)
	{
		switch (asterSize)
		{
		case 96:
		{
			new StoneAster(64, GetComponent<Transform>().myPosition.X, GetComponent<Transform>().myPosition.Y + 40.0f, mySpawner);
			new StoneAster(64, GetComponent<Transform>().myPosition.X - 40.0f, GetComponent<Transform>().myPosition.Y - 40.0f, mySpawner);
			new StoneAster(64, GetComponent<Transform>().myPosition.X + 40.0f, GetComponent<Transform>().myPosition.Y - 40.0f, mySpawner);
			hasCracked = true;
			break;
		}
		case 64:
		{
			new StoneAster(32, GetComponent<Transform>().myPosition.X, GetComponent<Transform>().myPosition.Y + 20.0f, mySpawner);
			new StoneAster(32, GetComponent<Transform>().myPosition.X - 20.0f, GetComponent<Transform>().myPosition.Y - 20.0f, mySpawner);
			new StoneAster(32, GetComponent<Transform>().myPosition.X + 20.0f, GetComponent<Transform>().myPosition.Y - 20.0f, mySpawner);
			hasCracked = true;
			break;
		}
		default:
			break;
		}

		
	}
	else if (health > 0)
	{
		GetComponent<Transform>().myPosition.X -= moveSpeedX * GameEngine::GetInstance()->GetDeltatime();
		GetComponent<Transform>().myPosition.Y += moveSpeedY * GameEngine::GetInstance()->GetDeltatime();

		float asterPosX = GetComponent<Transform>().myPosition.X;
		float asterPosY = GetComponent<Transform>().myPosition.Y;

		Vector2D colliderVelocity = (moveSpeedX, moveSpeedY);

		GetComponent<Collider>().SetVelocity(colliderVelocity);
		GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X, GetComponent<Transform>().myPosition.Y);
	}
}


