#pragma once
#include "Component.h"
#include "Vector2D.h"

struct Transform : public Component {

	Transform(float posX = 0, float posY = 0, float sclX = 1, float sclY = 1, float rotation = 0)
	{
		myPosition.X = posX;
		myPosition.Y = posY;
		myScale.X = sclX;
		myScale.Y = sclY;
		myRotation = rotation;
	}
	~Transform() {};

	Vector2D myPosition{};
	Vector2D myScale{};
	float myRotation{};

};
