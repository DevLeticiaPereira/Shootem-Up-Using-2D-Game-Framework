#include "Window.h"
#include "InitError.h"
#include "OpenGLContext.h"
#include <iostream>

Window::Window(std::string title, int windowWidth, int windowHeight) : myWindowWidth(windowWidth), myWindowHeight(windowHeight)
{
	sdlWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_OPENGL);

	if (sdlWindow == nullptr)
	{
		throw InitError();
	}
	
	context = new OpenGLContext(sdlWindow);
}

Window::~Window() 
{
	delete context;
	SDL_DestroyWindow(sdlWindow);
}

SDL_Window* Window::GetSDLWindow() 
{
	if (sdlWindow == nullptr)
		std::cout << "Window::GetSDLWindow() " << SDL_GetError() << std::endl;
	return sdlWindow;
}

void Window::Update()
{
	SDL_GL_SwapWindow(sdlWindow);
	//std::cout << "Window::updateSurface(): " << SDL_GetError() << std::endl;
}
//void Window::updateSurface()
//{
//	SDL_UpdateWindowSurface(sdlWindow);
//	//std::cout << "Window::updateSurface(): " << SDL_GetError() << std::endl;
//}

//SDL_Surface* Window::getSurface()
//{
//	SDL_Surface* windowSurface= SDL_GetWindowSurface(sdlWindow);
//	if (windowSurface == nullptr)
//		std::cout << "Window::getSurface()" << SDL_GetError() << std::endl;
//	return windowSurface;
//}



