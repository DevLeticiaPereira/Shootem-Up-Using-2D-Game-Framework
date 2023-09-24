#pragma once
#include "Entity.h"

enum class TextType { small, big };

class Text : public Entity
{
public:
	Text(std::string textToRender, TextType type = TextType::small, float angle = 0, float x = 0, float y = 0, int layer = 10);
	~Text() override;

	void Init() override;;
	void Update() override;

	void SetTimerForDestruction(float time);

	inline void SetMoveUp(float velocity) {	moveUpVel = velocity; }

private:

	bool shouldDestroy{ false };
	bool shouldMoveUp{ false };

	float moveUpVel{ 0 };

	float destructionDeltaTime{ 0 };
	float destructionTimer{ 0 };
	
	std::vector<char> charOrder
	{
	' ', '!', '"', '#', '$', '%', '&', '²',
	'(', ')', '*', '+', ',', '-', '.', '/',
	'0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', ':', ';', '<', '=', '>', '?',
	'©', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
	'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
	'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
	'X', 'Y', 'Z', '[', '³', ']', '^', '_',
	'`', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
	'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
	'p', 'q', 'r', 's', 't', 'u', 'v', 'w',
	'x', 'y', 'z', '{', '╎', '}', '~', '¤'
	};
};