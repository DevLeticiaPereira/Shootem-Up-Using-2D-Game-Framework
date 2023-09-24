#pragma once
#include "Enemy.h"
#include "Spawner.h"

class Drone :  public Enemy
{
public:
	Drone(float posX, float posY, Spawner* spawner);
	~Drone() override final;

	void Update() override final;
	void Init() override final;	

private:
	
	Animation* idleDrone{ nullptr };

	float spawnPosX{};
	float spawnPosY{};
	float time{0};

	float moveSpeed{ 130.0f };
	float magnitude{1.5};
	float frequency{2};
	float uniform{ 0.7071f };
};

