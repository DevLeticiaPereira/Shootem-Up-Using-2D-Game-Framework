#pragma once
#include <SDL.h>

class OpenGLContext
{
private:

	SDL_Window* sdlWindow{};
	SDL_GLContext context{};

public:

	OpenGLContext(SDL_Window* myWindow);
	~OpenGLContext();

	//void Init();
	//void SwapContext();

};

