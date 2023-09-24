#include "TextureManager.h"
#include <iostream>
#include "Texture.h"
#include "Renderer.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "Transform.h"

TextureManager* TextureManager::sInstance{ nullptr };

TextureManager::TextureManager()
{

    CreateNewFont("defaultText", "assets/Font8x8.bmp", 16, 8, characters);

}

TextureManager::~TextureManager()
{
    std::map<std::string, Texture*>::iterator it;
    for (it = textureMap.begin(); it != textureMap.end(); ++it)
    {
        delete it->second;
    }

    textureMap.clear();

}

void TextureManager::DrawTexture(std::string id, Transform* transform, float angle, bool flipHor, float r, float g, float b, float alpha) // could implement flip vertical and the rotation relkated to a especific point
{
    Texture* current = GetTexture(id);

    if (current == nullptr)
    {
        std::cout << "TextureManager::DrawTexture: Texture id not valid" << std::endl;

        return;
    }

    //int width = current->GetWidth();
    //int height = current->GetHeight();
    //
    //SDL_Rect scrRect = { 0, 0, width, height }; // which part of the image you wanna draw
    //SDL_Rect dstRect{}; // where you wanna draw

    //dstRect.x = static_cast<int>(transform->myPosition.X);
    //dstRect.y = static_cast<int>(transform->myPosition.Y);
    //dstRect.w = static_cast<int>(width * transform->myScale.X);
    //dstRect.h = static_cast<int>(height * transform->myScale.Y);


    Renderer::GetInstance()->Draw(transform, current, angle, 1, 1, 1, 1, flipHor, r, g, b, alpha);

}

void TextureManager::Clear()
{
    Renderer::GetInstance()->Clear();
}

void TextureManager::DropTexture(std::string id)
{
    delete textureMap[id];
    textureMap.erase(id);
}

void TextureManager::DrawFrame(std::string id, Transform* transform, int rowCurrent, int colCurrent, int rowTotal, int colTotal, float angle, bool flipHor, float r, float g, float b, float alpha)
{
    Texture* current = GetTexture(id);

    if (current == nullptr)
    {
        std::cout << "TextureManager::DrawTexture: Texture id not valid" << std::endl;

        return;
    }

    Renderer::GetInstance()->Draw(transform, current, static_cast<float>(angle), static_cast<float>(colCurrent), static_cast<float>(rowCurrent), static_cast<float>(colTotal), static_cast<float>(rowTotal), flipHor, r, g, b, alpha);
}

void TextureManager::DrawText(std::string textToRender, float angle, float x, float y, int layer, std::string id)
{

    std::map<char, Character> currentFont = fonts[id];


    for (char character : textToRender)
    {
        Character ch = currentFont[character];

        // now advance cursors for the next character

        Transform pos;
        pos.myPosition.X = x;
        pos.myPosition.Y = y;

        x += ch.Advance;

        DrawFrame(id, &pos, ch.rowCurrent, ch.colCurrent, ch.rowTotal, ch.colTotal, 0, false);
    }

}

void TextureManager::DrawSquare(Transform* position, float sizeX, float sizeY, float r, float g, float b, float alpha)
{
    //Renderer::GetInstance()->DrawSquare(position, position->myRotation, sizeX, sizeY, r, g, b, alpha);
}

Texture* TextureManager::GetTexture(std::string id)
{
    return (textureMap.count(id) > 0) ? textureMap[id] : nullptr;
}

Texture* TextureManager::LoadTexture(std::string id, std::string filePath)
{
    Texture* newTexture = nullptr;

    if (textureMap[id] == nullptr)
    {
        newTexture = new Texture(filePath);
        textureMap[id] = newTexture; // problemas de overwrite (?)
        if (newTexture == nullptr)
            std::cout << "Error creating texture from surface" << std::endl;
    }
    else
        std::cout << "Error Id already exists: " << id << std::endl;

    return newTexture;
}

void TextureManager::CreateNewFont(std::string id, std::string filePath, int rowTotal, int colTotal, std::vector<char> charFontOrder)
{
    if (fonts.find(id) != fonts.end())
    {
        return;
    }

    Texture* font = LoadTexture(id, filePath);

    int count = 0;

    int charCurrentRow = 1;
    int charCurrentCol = 1;

    std::map<char, Character> newFont;

    for (char character : charFontOrder)
    {
        Character newCharacter = {
            character,
            rowTotal,
            colTotal,
            charCurrentRow,
            charCurrentCol,
            font->GetWidth() / colTotal
        };

        newFont[character] = newCharacter;

        if (charCurrentCol < colTotal)
        {
            ++charCurrentCol;
        }
        else
        {
            charCurrentCol = 1;
            ++charCurrentRow;
        }
    }

    fonts[id] = newFont;
}