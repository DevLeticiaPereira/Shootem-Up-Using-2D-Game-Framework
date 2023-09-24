#pragma once

#include <string>
#include <vector>

#include "Component.h"
#include "Entity.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(std::string textureid, std::string filePath, float spriteRotation, int layer = 0, bool needsCut = false, int currentRow = 1, int currentCol = 1, int totalRows = 1, int totalCol = 1);
	~SpriteComponent() override {};

	bool Init() override final;

	void Draw() override final;
	
	void Update() override final;

	void SetOffset(Vector2D offsetFromEntity);

	void SetFilterColor(float r, float g, float b, float alpha);

	inline void SetFilterActive(bool active);

	inline void SetActive(bool shouldDraw) { isActive = shouldDraw; };

	inline int GetLayer() 
	{
		return myLayer;
	}

	int GetWidth() { return spriteWidth; }
	int GetHeight() { return spriteHeight; }

private:
	std::string myFilePath{};
	Transform* transform{ nullptr };
	std::string textureID{};
	class Texture* texture{ nullptr };

	int spriteWidth{ 0 };
	int spriteHeight{ 0 };

	float rotation{0};

	Vector2D offset{};
	
	bool isActive{ true };
	int myLayer{0};
	bool flip{ false };
	bool willBeCut{ false };
	int colCurrent{1};
	int colTotal{1};
	int rowCurrent{1};
	int rowTotal{1};
	
	float rColor;
	float gColor;
	float bColor;
	float myAlpha;
};