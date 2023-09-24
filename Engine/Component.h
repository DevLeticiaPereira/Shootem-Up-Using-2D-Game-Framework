#pragma once

class Entity;

class Component
{
public: 
	Component() = default;
	virtual ~Component() = default;

	Entity* entity{};

	virtual bool Init() { return true; }
	virtual void Draw() {}
	virtual void Update() {}

private:

};

