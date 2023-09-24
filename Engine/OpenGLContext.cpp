#include "OpenGLContext.h"
#include <glad.h>
#include "InitError.h"

OpenGLContext::OpenGLContext(SDL_Window* myWindow) : sdlWindow(myWindow)
{
	context = SDL_GL_CreateContext(sdlWindow);
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		throw InitError();
	}
}

OpenGLContext::~OpenGLContext()
{
	SDL_GL_DeleteContext(context);
}

//void OpenGLContext::Init()
//{
//	
//}

//void OpenGLContext::SwapContext()
//{
//	
//}
