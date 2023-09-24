#pragma once
#include "Entity.h"

class Bullet :  public Entity
{
public:
	Bullet(float posX, float posY, int currentBulletLevel);
	~Bullet() override;

	void Update() override;
	void Init() override;
	void WasHit(Entity* collidedObject) override;

private:
	Animation* bulletAnim{ nullptr };
	Animation* bulletDie{ nullptr };
	bool hasCollided;
	float spawnPosX{};
	float spawnPosY{};
	float firePower{};
};

