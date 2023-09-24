#include "Icon.h"
#include "Transform.h"

Icon::Icon(std::string textureID, std::string filePath, int posX, int posY, bool needsCut, int rowCurrent, int columnCurrent, int rowTotal, int columnTotal, int layer)
{
    AddComponent<SpriteComponent>(textureID, filePath, 0, layer, needsCut, rowCurrent, columnCurrent, rowTotal, columnTotal);

	GetComponent<Transform>().myPosition.X = posX;
	GetComponent<Transform>().myPosition.Y = posY;
}

Icon::~Icon()
{
	//Entity::~Entity();
}

void Icon::Init()
{
	Entity::Init();
}

void Icon::Update()
{
	Entity::Update();
}
