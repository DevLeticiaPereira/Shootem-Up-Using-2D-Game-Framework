#pragma once
#include "Entity.h"
#include "Component.h"

class PowerUp : public Entity
{
public:
	PowerUp() {};
	~PowerUp() override;

	void Update() override;
	void Init() override;
	virtual void WasHit(Entity* collidedObject) {};

	float moveSpeed{};
	float spawnPosX{};
	float spawnPosY{};
};