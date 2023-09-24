#pragma once

//#ifndef TEXTUREMANAGER_M
//#define TEXTUREMANAGER_M

#include "Texture.h"
#include "GameEngine.h"
#include "Transform.h"
#include "Entity.h"
#include <string>
#include <map>

struct Character {
	char letter;		   // Letter to render
	int rowTotal;          // Total number of rows
	int colTotal;          // Total number of columns
	int rowCurrent;        // Character current row
	int colCurrent;	       // Character current col
	int Advance;	       // Offset to advance to next character
};

enum class CharacterType { small, big };

class TextureManager {

public:

	TextureManager();
	~TextureManager();

	static TextureManager* GetInstance() { return sInstance = (sInstance != nullptr) ? sInstance : new TextureManager(); }

	void DrawTexture(std::string id, Transform* transform, float angle, bool flipHor = false, float r = 0, float g = 0, float b = 0, float alpha = 0);
	void Clear();

	void DropTexture(std::string id);
	void DrawFrame(std::string id, Transform* transform, int rowCurrent = 1, int colCurrent = 1, int rowTotal = 1, int colTotal = 1, float angle = 0, bool flipHor = false, float r = 0, float g = 0, float b = 0, float alpha = 0);
	void DrawText(std::string textToRender, float angle, float x, float y, int layer, std::string id = "defaultText");
	void DrawSquare(Transform* position, float sizeX, float sizeY, float r, float g, float b, float alpha);

	Texture* GetTexture(std::string id);
	Texture* LoadTexture(std::string id, std::string filePath);
	void CreateNewFont(std::string id, std::string filePath, int rowTotal, int colTotal, std::vector<char> charFontOrder);

private:

	static TextureManager* sInstance;

	//std::map<std::string, std::vector<char>> characterFontMap;

	std::vector<char> characters
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

	std::map<std::string, Texture*> textureMap{};

	std::map<std::string, std::vector<Entity*>> textMap{};

	std::map<std::string, std::map<char, Character>> fonts{};

	/*std::map<char, Character> smallCharacters{};
	std::map<char, Character> bigCharacters{};*/

};

//#endif // TEXTUREMANAGER_M