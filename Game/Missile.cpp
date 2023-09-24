#include "Missile.h"
#include "Spaceship.h"
#include "Companion.h"

Missile::Missile(float posX, float posY, float movementX, float movementY)
{
	AddComponent<Animator>();
	missileEnAnim = new Animation("missileEnAnim", "assets/EnWeap6.bmp", 1, 8, 1, 8, 1, 1, 4, false, 8, true, true, true);
	die = new Animation("missileExplode", "assets/explode16.bmp", 2, 5, 2, 5, 1, 1, 15, false, 5, false, true, true);
	GetComponent<Animator>().AddAnimation("missileEnAnim", missileEnAnim);
	spawnPosX = posX;
	spawnPosY = posY;
	missileMovX = movementX;
	missileMovY = movementY;
	hasCollided = false;
}

Missile::~Missile()
{
}

void Missile::Update()
{
	Entity::Update();

	if (!hasCollided)
	{
		GetComponent<Transform>().myPosition.X += (missileMovX * speed);
		GetComponent<Transform>().myPosition.Y += (missileMovY * speed);

		GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X, GetComponent<Transform>().myPosition.Y);
	}
	else
	{
		if (!GetComponent<Animator>().AnimationIsPlaying())
		{
			Destroy();
		}

		GetComponent<Collider>().SetBullet(false);
	}
	
	if (GetComponent<Transform>().myPosition.X > ((GameEngine::GetInstance()->GameWindowWidht()) + 10) ||
		GetComponent<Transform>().myPosition.X < -10)
	{
		Destroy();
	}
	if (GetComponent<Transform>().myPosition.Y > ((GameEngine::GetInstance()->GameWindowHeight()) + 10) ||
		GetComponent<Transform>().myPosition.Y < -10)
	{
		Destroy();
	}

	GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X, GetComponent<Transform>().myPosition.Y);

}

void Missile::Init()
{
	Entity::Init();
	GetComponent<Transform>().myPosition.X = spawnPosX;
	GetComponent<Transform>().myPosition.Y = spawnPosY;

	if (HasComponent<Animator>())
		GetComponent<Animator>().AddAnimation("missileExplode", die);

	float colliderHeight = static_cast<float>(GetComponent<Animator>().GetAnimationByName("missileEnAnim")->frameHeight);
	float colliderWidth = static_cast<float>(GetComponent<Animator>().GetAnimationByName("missileEnAnim")->frameWidth);

	AddComponent<Collider>().AddAttributes("Missile", this, Collider::BodyType::dynamicBody,
											GetComponent<Transform>().myPosition.X,
											GetComponent<Transform>().myPosition.Y,
											colliderWidth, colliderHeight, true, 0.0f);
}

void Missile::WasHit(Entity* collidedObject)
{
	if (collidedObject->GetComponent<Collider>().GetId() == "Bullet")
	{
		hasCollided = true;
		if (HasComponent<Animator>())
			GetComponent<Animator>().PlayFromStart("missileExplode", false, true);
	}

	if (collidedObject->GetComponent<Collider>().GetId() == "Spaceship")
	{
		hasCollided = true;
		Spaceship* currentPlayer = static_cast<Spaceship*>(collidedObject);
		currentPlayer->ChangeBulletLevel(false);
		currentPlayer->ApplyDamage(20);

		if (HasComponent<Animator>())
			GetComponent<Animator>().PlayFromStart("missileExplode", false, true);
	}

	if (collidedObject->GetComponent<Collider>().GetId() == "Companion")
	{
		Companion* playerCompanion = static_cast<Companion*>(collidedObject);

		if (playerCompanion->IsTaken())
		{
			hasCollided = true;
			playerCompanion->ChangeBulletLevel(false);
			playerCompanion->ApplyDamage(20);

			if (HasComponent<Animator>())
				GetComponent<Animator>().PlayFromStart("missileExplode", false, true);
		}
	}
}
