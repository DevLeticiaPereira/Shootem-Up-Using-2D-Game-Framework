#pragma once
#include "Entity.h"

class Companion : public Entity
{
public:
	Companion(float posX, float posY, class Spawner* spawner);
	~Companion();

	class Spawner* companionSpawner{ nullptr };
	class Spawner* GetSpawner();

	int maxHealth{};

	void Init();
	void Update();
	void Attack();
	void ApplyShield(int shieldValue);
	void ApplyDamage(int damageReceived);
	void SetDisplacement(Vector2D displacementVector);
	void ChangeBulletLevel(bool willIncrease);
	void TakeCompanion(bool isTaken);
	void SetPlayerReference(class Spaceship* player);
	bool IsTaken();

private:
	int health{};
	int bulletLevel{};
	int bulletMinLevel{};
	int bulletMaxLevel{};
	float spawnPosX;
	float spawnPosY;
	int displacementX{0};
	int displacementY{0};
	bool isTaken{ false };
	float moveSpeed{-60.0f};
	float bulletDeltaTime{ 0.1f };
	float bulletCoolDown{ 0.15f };
	Animation* companionIdle{ nullptr };
	class Spaceship* currentPlayer{};
};
