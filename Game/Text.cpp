#include "Text.h"
#include "Transform.h"

Text::Text(std::string text, TextType type, float angle, float posX, float posY, int layerText)
{
	switch (type)
	{
	case TextType::small:
	{
		AddComponent<TextComponent>(text, angle, posX, posY, layerText);
		break;
	}

	case TextType::big:
	{
		AddComponent<TextComponent>(text, angle, posX, posY, layerText);
		GetComponent<TextComponent>().SetNewFont("XenonBigFont", "assets/font16x16.bmp", 12, 8, charOrder);
		break;
	}

	default:
		break;
	}

	GetComponent<Transform>().myPosition.X = posX;
	GetComponent<Transform>().myPosition.Y = posY;
}

Text::~Text()
{
	//Entity::~Entity();
}

void Text::Init()
{
	Entity::Init();
}

void Text::Update()
{
	Entity::Update();
	
	if (shouldDestroy)
	{
		destructionDeltaTime += GameEngine::GetInstance()->GetDeltatime();

		if (destructionDeltaTime >= destructionTimer)
		{
			
			Destroy();
			
		}
	}

	GetComponent<Transform>().myPosition.Y += moveUpVel;
	

}

void Text::SetTimerForDestruction(float time)
{
	shouldDestroy = true;
	destructionTimer = time;
}
