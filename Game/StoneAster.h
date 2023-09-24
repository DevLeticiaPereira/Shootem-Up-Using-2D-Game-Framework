#pragma once
#include "Enemy.h"

class StoneAster : public Enemy
{
public:
	StoneAster(int size, float posX, float posY, class Spawner* spawner);
	~StoneAster() override final;

	void Update() override final;
	void Init() override final;

private:

	bool hasCracked{ false };

	Animation* idle{ nullptr };

	float spawnPosX{};
	float spawnPosY{};


	int asterSize{};
	float moveSpeedX{ 2.0f };
	float moveSpeedY{ 0 };
	float uniform = 0.7071f;
};
