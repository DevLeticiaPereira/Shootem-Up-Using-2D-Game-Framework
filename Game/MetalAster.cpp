#include "MetalAster.h"
#include "Spawner.h"

MetalAster::MetalAster(int size, float posX, float posY, Spawner* spawner)
{
	AddComponent<Animator>();
	mySpawner = spawner;
	spawnPosX = posX;
	spawnPosY = posY;
	asterSize = size;

	switch (asterSize)
	{
		case 96:
		{
			idle = new Animation("idleMetal96", "assets/MAster96.bmp", 5, 5, 5, 5, 1, 1, 10, false, 2, true, true, true);
			die = new Animation("enemydie64", "assets/explode64.bmp", 2, 5, 2, 5, 1, 1, 15, false, 2, false, true, true);
			moveSpeedX = 40;
			break;
		}
		case 64:
		{
			idle = new Animation("idleMetal64", "assets/MAster64.bmp", 3, 8, 3, 8, 1, 1, 10, false, 2, true, true, true);
			die = new Animation("enemydie32", "assets/explode32.bmp", 2, 5, 2, 5, 1, 1, 30, false, 2, false, true, true);
			moveSpeedX = 55;
			break;
		}
		case 32:
		{
			idle = new Animation("idleMetal32", "assets/MAster32.bmp", 2, 8, 2, 8, 1, 1, 8, false, 2, true, true, true);
			die = new Animation("enemydie16", "assets/explode16.bmp", 2, 5, 2, 5, 1, 1, 30, false, 2, false, true, true);
			moveSpeedX = 75;
			break;
		}
		default:
		break;
	}

	GetComponent<Animator>().AddAnimation("idle", idle);

	float colliderHeight = static_cast<float>(GetComponent<Animator>().GetAnimationByName("idle")->frameHeight);
	float colliderWidth = static_cast<float>(GetComponent<Animator>().GetAnimationByName("idle")->frameWidth);

	AddComponent<Collider>().AddAttributes("Enemy", this, Collider::BodyType::dynamicBody,
		GetComponent<Transform>().myPosition.X, GetComponent<Transform>().myPosition.Y,
		colliderHeight, colliderWidth, true, 0.0f);

	canReceiveDamage = false;
	health = 10;
}

MetalAster::~MetalAster()
{
	//Aster::~Aster();
}

void MetalAster::Init()
{
	Enemy::Init();

	GetComponent<Transform>().myPosition.X = spawnPosX;
	GetComponent<Transform>().myPosition.Y = spawnPosY;

	moveSpeedY = static_cast<float>((rand() % 16) );
	int sighn = rand() % (2);
	if (sighn != 1)
	{
		moveSpeedY *= -1;
	}

}

void MetalAster::Update()
{
	Enemy::Update();

	if (health > 0)
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


