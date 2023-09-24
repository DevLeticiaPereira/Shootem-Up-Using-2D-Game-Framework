#pragma once
#include "Enemy.h"
#include "Spawner.h"

class Loner : public Enemy
{
public:
	Loner(float posX, float posY, Spawner* spawner);
	~Loner() override final;

	void Update() override final;
	void Init() override final;

	void Attack();

private:

	Animation* idleLoner{ nullptr };
	float spawnPosX{};
	float spawnPosY{};
	float moveSpeed = 100.0f;
	float uniform = 0.7071f;

	float missileDeltaTime{0};
	float missileCoolDown{2.f};

	Vector2D playerPosition = (0.0f, 0.0f);
};

