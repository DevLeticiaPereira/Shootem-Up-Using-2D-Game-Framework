#pragma once
#include "Entity.h"

class BackGround : Entity
{

public:

	BackGround(Animation* anim, std::string animName, float posX, float posY, float velocity = 3);
	~BackGround() override;

	void Update() override;
	void Init() override;

protected:

	int windowWidth;
	int windowHeight;
	std::string myAnimName;
	int paralaxVel{ 3 };
	Animation* animation;

};

