#include "TextComponent.h"
#include "TextureManager.h"

TextComponent::TextComponent(std::string textToRender, float angle, float x, float y, int layer, std::string id)
{
	fontId = id;
	text = textToRender;
	rotation = angle;
	posX = x;
	posY = y;
	currentLayer = layer;

}

bool TextComponent::Init()
{
	transform = &entity->GetComponent<Transform>();

	return true;
}

void TextComponent::Draw()
{

	TextureManager::GetInstance()->DrawText(text, transform->myRotation, transform->myPosition.X, transform->myPosition.Y, currentLayer, fontId);

}

void TextComponent::Update()
{
	transform = &entity->GetComponent<Transform>();
}

void TextComponent::SetNewFont(std::string newId, std::string filePath, int rowTotal, int colTotal, std::vector<char> charFontOrder)
{
	fontId = newId;
	TextureManager::GetInstance()->CreateNewFont(newId, filePath, rowTotal, colTotal, charFontOrder);
}
