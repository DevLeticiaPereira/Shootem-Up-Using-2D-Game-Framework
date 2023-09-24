#pragma once
#include "Entity.h"
#include "PowerUp.h"
#include "Spawner.h"
#include "Component.h"

class WeaponPowerUp : public PowerUp
{
public:
	WeaponPowerUp(float posX, float posY, Spawner* spawner);
	~WeaponPowerUp() override final;

	void Update() override final;
	void Init() override final;
	void WasHit(Entity* collidedObject) override ;

private:
	Spawner* mySpawner{ nullptr };
	Animation* idlePowerUp{ nullptr };
};
