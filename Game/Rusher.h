#pragma once
#include "Enemy.h"
#include "Spawner.h"

class Rusher :  public Enemy
{
public:
	Rusher(float posX, float posY, Spawner* spawner);
	~Rusher() override final;

	void Update() override final;
	void Init() override final;	

private:
	
	Animation* idleRusher{ nullptr };
	float spawnPosX{};
	float spawnPosY{};
	float textureRotation{ 0 };
	float moveSpeed{ 100.0f };
	float uniform{ 0.7071f };
};

