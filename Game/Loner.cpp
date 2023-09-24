#include "Loner.h"
#include "Missile.h"

Loner::Loner(float posX, float posY, Spawner* spawner)
{

	AddComponent<Animator>();
	mySpawner = spawner;
	spawnPosX = posX;
	spawnPosY = posY;

	if(spawnPosX < static_cast<float>(GameEngine::GetInstance()->GameWindowWidht() / 2))
		idleLoner = new Animation("idleLoner", "assets/LonerA.bmp", 4, 4, 4, 4, 1, 1, 8, true, 2, true, true, true);
	else
		idleLoner = new Animation("idleLoner", "assets/LonerA.bmp", 4, 4, 4, 4, 1, 1, 8, false, 2, true, true, true);
	
	GetComponent<Animator>().AddAnimation("idle",idleLoner);

	float colliderHeight = static_cast<float>(GetComponent<Animator>().GetAnimationByName("idle")->frameHeight);
	float colliderWidth = static_cast<float>(GetComponent<Animator>().GetAnimationByName("idle")->frameWidth);

	AddComponent<Collider>().AddAttributes("Enemy", this, Collider::BodyType::dynamicBody,
											 GetComponent<Transform>().myPosition.X,
											 GetComponent<Transform>().myPosition.Y, 
											 colliderWidth, colliderHeight, true, 0.0f);
	
	health = 10;
}

Loner::~Loner()
{
	//Enemy::~Enemy();
}

void Loner::Init()
{
	Enemy::Init();
	score = 100;
	GetComponent<Transform>().myPosition.X = spawnPosX;
	GetComponent<Transform>().myPosition.Y = spawnPosY;
	GetComponent<Animator>().PlayFromStart("idle", true, true);
	
}

void Loner::Update()
{
	Enemy::Update();

	missileDeltaTime += GameEngine::GetInstance()->GetDeltatime();

	if (missileDeltaTime > missileCoolDown && health > 0)
	{
		Attack();
	}

	if (spawnPosY > static_cast<float>(GameEngine::GetInstance()->GameWindowHeight() / 2))
	{
		if (health > 0)
		{
			GetComponent<Transform>().myPosition.Y -= (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform);
			GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X, GetComponent<Transform>().myPosition.Y);
		}

	}
	else
	{
		if (health > 0)
		{
			GetComponent<Transform>().myPosition.Y += (moveSpeed * GameEngine::GetInstance()->GetDeltatime() * uniform);
			GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X, GetComponent<Transform>().myPosition.Y);
		}

	}
	
}

void Loner::Attack()
{
	float x, y{};
	x = GetComponent<Transform>().myPosition.X;
	y = GetComponent<Transform>().myPosition.Y - 30.0f;

	playerPosition = mySpawner->GetPlayerPosition();

	Vector2D missileMovement{};
	missileMovement.X = playerPosition.X - GetComponent<Transform>().myPosition.X;
	missileMovement.Y = (playerPosition.Y + 20.0f) - GetComponent<Transform>().myPosition.Y;

	missileMovement.NormalizeVector();

	Missile* missile = new Missile(x, y, missileMovement.X, missileMovement.Y);
	missileDeltaTime = 0;
}
