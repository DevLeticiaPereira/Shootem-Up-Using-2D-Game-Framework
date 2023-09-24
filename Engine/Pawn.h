#pragma once
#include "Entity.h"

class Pawn : public Entity
{

public:
	Pawn();

	int health;

	inline void Update() override { Entity::Update(); };

	inline void Init() override { Entity::Init(); };

	virtual void OnKeyDown(std::string keycode) {};

	virtual void OnKeyUp(std::string keycode) {};

	virtual void OnButtonDown(std::string button) {};

	virtual void OnButtonUp(std::string button) {};

	virtual void OnAxisChange(float axisValue, bool Yaxis) {};

	virtual void CheckKeyState() {};

private:
	std::map<int, std::string> KeyboardKeystate;
};
#pragma once
