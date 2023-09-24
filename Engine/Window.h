#pragma once
#include <SDL.h>
#include <string>

class Window
{
public:
	Window(std::string title, int windowWidth, int windowHeight);

	SDL_Window* GetSDLWindow();

	//SDL_Surface* getSurface();

	//void updateSurface();
	void Update();

	inline int GetWindowHeigh() { return myWindowHeight; }
	inline int GetWindowWidth() { return myWindowWidth; }

	~Window();
private:

	SDL_Window* sdlWindow;
	class OpenGLContext* context;
	int myWindowWidth, myWindowHeight;
};
