#include "Bullet.h"
#include "Enemy.h"

Bullet::Bullet(float posX, float posY, int currentBulletLevel)
{
	AddComponent<Animator>();
	GetComponent<Transform>().myRotation = -90.0f;
	bulletDie = new Animation("bulletExplode", "assets/explode16.bmp", 2, 5, 2, 5, 1, 1, 15, false, 3, false, true, true);

	switch (currentBulletLevel)
	{
		case (1):
		{
			bulletAnim = new Animation("bulletAnim", "assets/missile.bmp", 3, 2, 1, 2, 1, 1, 4, false, 3, true, true, true);
			GetComponent<Animator>().AddAnimation("bulletAnim", bulletAnim);
			firePower = 10.0f;
			break;
		}

		case (2):
		{
			bulletAnim = new Animation("bulletAnim", "assets/missile.bmp", 3, 2, 2, 2, 2, 1, 4, false, 3, true, true, true);
			GetComponent<Animator>().AddAnimation("bulletAnim", bulletAnim);
			firePower = 25.0f;
			break;
		}

		case (3):
		{
			bulletAnim = new Animation("bulletAnim", "assets/missile.bmp", 3, 2, 3, 2, 3, 1, 4, false, 3, true, true, true);
			GetComponent<Animator>().AddAnimation("bulletAnim", bulletAnim);
			firePower = 50.0f;
			break;
		}

		default:
		{
			bulletAnim = new Animation("bulletAnim", "assets/missile.bmp", 3, 2, 1, 2, 1, 1, 4, false, 3, true, true, true);
			GetComponent<Animator>().AddAnimation("bulletAnim", bulletAnim);
			firePower = 10.0f;
		}
			break;
	}

	spawnPosX = posX;
	spawnPosY = posY;
	hasCollided = false;
}

Bullet::~Bullet()
{
	//Entity::~Entity();
}

void Bullet::Update()
{
	Entity::Update();

	if (!hasCollided)
	{
		GetComponent<Transform>().myPosition.X += 10;

		float bulletPosX = GetComponent<Transform>().myPosition.X;
		float bulletPosY = GetComponent<Transform>().myPosition.Y;

		Vector2D colliderVelocity = (bulletPosX, bulletPosY);

		GetComponent<Collider>().SetVelocity(colliderVelocity);
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

}

void Bullet::Init()
{
	Entity::Init();

	if (HasComponent<Animator>())
		GetComponent<Animator>().AddAnimation("bulletExplode", bulletDie);

	GetComponent<Transform>().myPosition.X = spawnPosX;
	GetComponent<Transform>().myPosition.Y = spawnPosY;

	float colliderHeight = static_cast<float>(GetComponent<Animator>().GetAnimationByName("bulletAnim")->frameHeight);
	float colliderWidth = static_cast<float>(GetComponent<Animator>().GetAnimationByName("bulletAnim")->frameWidth);

	AddComponent<Collider>().AddAttributes("Bullet", this, Collider::BodyType::dynamicBody,
									       GetComponent<Transform>().myPosition.X,
										   GetComponent<Transform>().myPosition.Y,
											colliderWidth, colliderHeight, true, 0.0f);


}

void Bullet::WasHit(Entity* collidedObject)
{
	if (collidedObject->GetComponent<Collider>().GetId() == "Enemy" || 
		collidedObject->GetComponent<Collider>().GetId() == "Missile")
	{
		if (collidedObject->GetComponent<Collider>().GetId() == "Enemy")
		{
			Enemy* enemy = static_cast<Enemy*>(collidedObject);
			enemy->ApplyDamage(firePower, this);
		}

		hasCollided = true;
		if (HasComponent<Animator>())
			GetComponent<Animator>().PlayFromStart("bulletExplode", false, true);
	}
		
}
