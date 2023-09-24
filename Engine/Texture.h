#pragma once
#include <SDL.h>
#include "Window.h"
#include <iostream>

class Texture
{
public:

	Texture(const std::string& path);
	~Texture();


	void Bind(unsigned int slot = 0); //slot is a way of bind more than one texture in one surface
	void Unbind();

	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }

private:

	unsigned int rendererID;
	std::string filePath;
	unsigned char* localBuffer;
	int width, height, bpp;

};