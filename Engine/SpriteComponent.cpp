#include "SpriteComponent.h"
#include "TextureManager.h"


SpriteComponent::SpriteComponent(std::string textureid, std::string filePath, float spriteRotation, int layer, bool needsCut, int currentRow, int currentCol, int totalRows, int totalCol)
{
	textureID = textureid;
	myFilePath = filePath;
	rotation = spriteRotation;
	myLayer = layer;
	willBeCut = needsCut;
	rowCurrent = currentRow;
	colCurrent = currentCol;
	rowTotal = totalRows;
	colTotal = totalCol;
	offset = Vector2D(0, 0);
}

bool SpriteComponent::Init()
{
	transform = &entity->GetComponent<Transform>();

	if (TextureManager::GetInstance()->GetTexture(textureID) == nullptr)
	{
		texture = TextureManager::GetInstance()->LoadTexture(textureID, myFilePath);
	}
	else
	{
		texture = TextureManager::GetInstance()->GetTexture(textureID);
	}

	spriteWidth = static_cast<int>(texture->GetWidth() / colCurrent);
	spriteHeight = static_cast<int>(texture->GetHeight() / rowCurrent);

	return true;
}

void SpriteComponent::Draw()
{
	if (isActive)
	{
		Transform* texPos = new Transform;
		texPos->myPosition.X += transform->myPosition.X + offset.X;
		texPos->myPosition.Y += transform->myPosition.Y + offset.Y;
		texPos->myRotation = transform->myRotation;
		texPos->myScale = transform->myScale;

		if (!willBeCut)
		{
			TextureManager::GetInstance()->DrawTexture(textureID, texPos, rotation, flip, rColor, gColor, bColor, myAlpha);
		}
		else
		{
			TextureManager::GetInstance()->DrawFrame(textureID, texPos, rowCurrent, colCurrent, rowTotal, colTotal, 0, false, rColor, gColor, bColor, myAlpha);
		}

		delete texPos;
	}
	
}

void SpriteComponent::Update()
{
	transform = &entity->GetComponent<Transform>();
}

void SpriteComponent::SetOffset(Vector2D offsetFromEntity)
{
	offset = offsetFromEntity;
}

void SpriteComponent::SetFilterColor(float r, float g, float b, float alpha)
{
	rColor = r;
	gColor = g;
	bColor = b;
	myAlpha = alpha;
}

inline void SpriteComponent::SetFilterActive(bool active)
{
		if (active) { myAlpha = 1; }
		else { myAlpha = 0; }
}
