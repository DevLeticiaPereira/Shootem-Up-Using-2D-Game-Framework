#pragma once
#include "Entity.h"

class Missile :  public Entity
{

public:
	Missile(float posX, float posY, float movementX, float movementY);
	~Missile() override;

	void Update() override;
	void Init() override;
	void WasHit(Entity* collidedObject) override;

private:
	Animation* missileEnAnim{ nullptr };
	Animation* die{ nullptr };
	float spawnPosX{};
	float spawnPosY{};
	float missileMovX{};
	float missileMovY{};
	float speed = 5.0f;
	bool hasCollided;
};

