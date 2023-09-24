#include "Drone.h"
#include <math.h>

Drone::Drone(float posX, float posY, Spawner* spawner)
{
	
	AddComponent<Animator>();
	mySpawner = spawner;
	spawnPosX = posX;
	spawnPosY = posY;
	idleDrone = new Animation("idleDrone", "assets/drone.bmp", 2, 8, 2, 8, 1, 1, 24, false, 3, true, true, true);
	GetComponent<Transform>().myRotation = 0;

	GetComponent<Animator>().AddAnimation("idleDrone", idleDrone);

	health = 10;
}

Drone::~Drone() { }

void Drone::Init()
{
	Enemy::Init();

	GetComponent<Transform>().myPosition.X = spawnPosX;
	GetComponent<Transform>().myPosition.Y = spawnPosY;
	GetComponent<Animator>().PlayFromStart("idleDrone", true, true);

	float colliderHeight = static_cast<float>(GetComponent<Animator>().GetAnimationByName("idleDrone")->frameHeight);
	float colliderWidth = static_cast<float>(GetComponent<Animator>().GetAnimationByName("idleDrone")->frameWidth);

	AddComponent<Collider>().AddAttributes("Enemy", this, Collider::BodyType::dynamicBody,
		GetComponent<Transform>().myPosition.X,
		GetComponent<Transform>().myPosition.Y,
		colliderWidth, colliderHeight, true, 0.0f);
}

void Drone::Update()
{
	Enemy::Update();

	if (health > 0)
	{
		time += GameEngine::GetInstance()->GetDeltatime();

		if (spawnPosX < static_cast<float>(GameEngine::GetInstance()->GameWindowWidht() / 2))
		{

			GetComponent<Transform>().myPosition.X += (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform);
		}
		else
		{

			GetComponent<Transform>().myPosition.X -= (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform);

		}


		GetComponent<Transform>().myPosition.Y = GetComponent<Transform>().myPosition.Y + (sin(time * frequency) * magnitude);
		GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X, GetComponent<Transform>().myPosition.Y);

	}
}