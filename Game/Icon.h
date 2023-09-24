#pragma once
#include "Entity.h"

class Icon : public Entity
{
public:
	Icon(std::string textureID, std::string filePath, int posX, int posY, bool needsCut, int rowCurrent, int columnCurrent, int rowTotal, int columnTotal, int layer = 0);

	~Icon() override;

	void Init() override;;
	void Update() override;

	Vector2D GetIconColor() { return iconColor; }

private:

	Vector2D iconColor = { 1.f, 1.f };
};