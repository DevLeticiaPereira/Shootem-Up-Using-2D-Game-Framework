#pragma once
#include "Entity.h"
#include "Component.h"

class Enemy : public Entity
{
public:
	Enemy();
	~Enemy() override;

	void Update() override;
	void Init() override;
	void WasHit(Entity* collidedObject) override;

	void ApplyDamage(float damage, Entity* collidedObject);

	int GetScore() { return score; }
	bool ReceivesDamage() { return canReceiveDamage; }

protected: 

	Animation* die{nullptr};

	int score{50};
	float health{50};
	float time{};
	float loseDamageRate{1};
	bool canReceiveDamage{ true };
	class Spawner* mySpawner = nullptr;
};

