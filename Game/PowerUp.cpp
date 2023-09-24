#include "PowerUp.h"
#include "Spaceship.h"

PowerUp::~PowerUp()
{
	//Entity::~Entity();
}

void PowerUp::Update()
{
	Entity::Update();

	GetComponent<Transform>().myPosition.X += moveSpeed * GameEngine::GetInstance()->GetDeltatime();
	GetComponent<Collider>().SetPosition(GetComponent<Transform>().myPosition.X, GetComponent<Transform>().myPosition.Y);
}

void PowerUp::Init()
{
	Entity::Init();
}
