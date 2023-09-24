#pragma once
#include "Entity.h"
#include "PowerUp.h"
#include "Spawner.h"

class ShieldPowerUp : public PowerUp
{
public:
	ShieldPowerUp(float posX, float posY, Spawner* spawner);
	~ShieldPowerUp() override final;

	void Update() override final;
	void Init() override final;
	void WasHit(Entity* collidedObject) override;

private:
	Spawner* mySpawner{ nullptr };
	Animation* idlePowerUp{ nullptr };
};
