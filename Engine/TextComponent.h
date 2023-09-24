#pragma once

#include <string>
#include <vector>

#include "Component.h"
#include "Entity.h"

//enum class LetterType { small, big };

class TextComponent : public Component
{
public:
	TextComponent(std::string textToRender, float angle, float x, float y, int layer, std::string id = "defaultText");
	~TextComponent() override {};

	bool Init() override final;

	void Draw() override final;

	void Update() override final;

	void SetNewFont(std::string newId, std::string filePath, int rowTotal, int colTotal, std::vector<char> charFontOrder);

	inline int GetLayer() { return currentLayer; }

private:
	std::string text{};
	Transform* transform{ nullptr };
	float rotation;
	int posY{};
	int posX{};
	int currentLayer;
	bool staticText;
	std::string fontId;
};