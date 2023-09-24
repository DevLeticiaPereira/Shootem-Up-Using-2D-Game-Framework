#include "Rusher.h"

Rusher::Rusher(float posX, float posY, Spawner* spawner)
{
	
	AddComponent<Animator>();
	mySpawner = spawner;
	spawnPosX = posX;
	spawnPosY = posY;
	idleRusher = new Animation("idleRusher", "assets/rusher.bmp", 6, 4, 6, 4, 1, 1, 24, false, 3, true, true, true);

	if (spawnPosX > static_cast<float>(GameEngine::GetInstance()->GameWindowWidht() / 2))
		GetComponent<Transform>().myRotation = -90.f;
	else
		GetComponent<Transform>().myRotation = 90.f;

	GetComponent<Animator>().AddAnimation("idleRusher", idleRusher);

	health = 10;
}

Rusher::~Rusher() {}

void Rusher::Update()
{
	Enemy::Update();

	if (spawnPosX < static_cast<float>(GameEngine::GetInstance()->GameWindowWidht() / 2))
	{
		if (health > 0)
		{
			GetComponent<Transform>().myPosition.X += (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform);
			GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X, GetComponent<Transform>().myPosition.Y);
		}
	}
	else
	{
		if (health > 0)
		{
			GetComponent<Transform>().myPosition.X -= (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform);
			GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X, GetComponent<Transform>().myPosition.Y);
		}
	}
}

void Rusher::Init()
{
	Enemy::Init();
	GetComponent<Transform>().myPosition.X = spawnPosX;
	GetComponent<Transform>().myPosition.Y = spawnPosY;

	float colliderHeight = static_cast<float>(GetComponent<Animator>().GetAnimationByName("idleRusher")->frameHeight);
	float colliderWidth = static_cast<float>(GetComponent<Animator>().GetAnimationByName("idleRusher")->frameWidth);

	AddComponent<Collider>().AddAttributes("Enemy", this, Collider::BodyType::dynamicBody,
										   GetComponent<Transform>().myPosition.X,
										   GetComponent<Transform>().myPosition.Y,
										   colliderWidth, colliderHeight, true, 0.0f);
}
