#include "GameEngine.h"
#include "SDLWrapper.h"
#include "Window.h"
#include "CollisionListener.h"
#include "TextureManager.h"
#include "Renderer.h"
#include "InputManager.h"
#include "Texture.h"
#include "Level.h"
#include "Pawn.h"

#include <iostream>

GameEngine* GameEngine::instance = nullptr;

GameEngine::GameEngine()
{
	prevTime = 0;
	currentTime = 0;
	deltaTime = 0;

	b2Vec2 gravity(0.0f, -10.0f);
	world = new b2World(gravity);
}

void GameEngine::init(std::string windowTitle, int windowWidth, int windowHeight)
{
	sdl = new SDLWrapper(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) < 0)
	{
		std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;

		SDL_Quit();
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	window = new Window(windowTitle, windowWidth, windowHeight);

	defaultLevel = CreateNewLevel("defaultLevel");
	myWindowWidth = windowWidth;
	myWindowHeigth = windowHeight;

	if (currentLevel == nullptr)
	{
		ActivateLevelByName("defaultLevel");
		currentLevel = defaultLevel;
	}

	world->SetContactListener(CollisionListener::GetInstance());
	textureManager = TextureManager::GetInstance();
}

void GameEngine::start()
{                          
	currentLevel->Init();

	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	bool isRunning = true;
	SDL_Event ev;

	while (isRunning)
	{
		prevTime = currentTime;
		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - prevTime) / 1000.0f;

		world->Step(timeStep, velocityIterations, positionIterations);

		while (SDL_PollEvent(&ev) != 0)
		{
			if (ev.type == SDL_QUIT)
				isRunning = false;

			switch (ev.type)
			{
				case SDL_CONTROLLERDEVICEADDED:
				{
					std::cout << "A controller was connected. " << std::endl;

					// Mapping controller
					int controllerIndex = 0;
					std::map<int, SDL_GameController*> temporaryControllerIndexMap = InputManager::GetInstance()->ControllerIndex;

					if (temporaryControllerIndexMap.size())
					{
						bool controllerIncluded = false;

						std::map<int, SDL_GameController*>::iterator it;
						for (it = temporaryControllerIndexMap.begin(); it != temporaryControllerIndexMap.end(); it++)
						{
							// If a controller was removed and there is a free index
							if (it->second == nullptr)
							{
								it->second = SDL_GameControllerOpen(ev.cdevice.which);
								controllerIndex = it->first;
								InputManager::GetInstance()->UpdateControllerIndex(temporaryControllerIndexMap);
								controllerIncluded = true;
								break;
							}
						}

						// If there is no free index
						if (controllerIncluded == false)
						{
							temporaryControllerIndexMap.insert({ temporaryControllerIndexMap.size() , SDL_GameControllerOpen(ev.cdevice.which) });
							controllerIndex = static_cast<int>(temporaryControllerIndexMap.size() - 1);
							InputManager::GetInstance()->UpdateControllerIndex(temporaryControllerIndexMap);
						}

					}
					else
					{
						// Add controll at index 0
						temporaryControllerIndexMap.insert({ temporaryControllerIndexMap.size() , SDL_GameControllerOpen(ev.cdevice.which) });
						controllerIndex = static_cast<int>(temporaryControllerIndexMap.size() - 1);
						InputManager::GetInstance()->UpdateControllerIndex(temporaryControllerIndexMap);
					}

					InputManager::GetInstance()->MapNewController(controllerIndex);

					// Associate controller with available pawn
					std::map<Pawn*, SDL_GameController*> pawnController = InputManager::GetInstance()->ControlledPawn;
					if (pawnController.size())
					{
						std::map<Pawn*, SDL_GameController*>::iterator it;
						for (it = pawnController.begin(); it != pawnController.end(); ++it)
						{
							if (it->second == nullptr)
							{
								it->second = SDL_GameControllerOpen(ev.cdevice.which);
								std::cout << "Found a pawn! " << std::endl;
								std::cout << SDL_GameControllerNameForIndex(ev.cdevice.which) << " pawn: " << it->first << std::endl;
								InputManager::GetInstance()->UpdateController(pawnController);
								break;
							}
						}
					}

					break;
				}

				case SDL_CONTROLLERDEVICEREMOVED:
				{
					std::cout << "A controller was disconnected. " << std::endl;

					// Remove controller from index map
					std::map<int, SDL_GameController*> temporaryControllerIndexMap = InputManager::GetInstance()->ControllerIndex;
					std::map<int, SDL_GameController*>::iterator it;
					for (it = temporaryControllerIndexMap.begin(); it != temporaryControllerIndexMap.end(); ++it)
					{
						if (it->second == SDL_GameControllerFromInstanceID(ev.cdevice.which))
						{
							it->second = nullptr;
							break;
						}
					}
					InputManager::GetInstance()->UpdateControllerIndex(temporaryControllerIndexMap);

					// Dissociate pawn connected with controller
					std::map<Pawn*, SDL_GameController*> pawnController = InputManager::GetInstance()->ControlledPawn;
					if (pawnController.size())
					{
						std::map<Pawn*, SDL_GameController*>::iterator it;
						for (it = pawnController.begin(); it != pawnController.end(); ++it)
						{
							if (it->second == SDL_GameControllerFromInstanceID(ev.cdevice.which))
							{
								it->second = nullptr;
								InputManager::GetInstance()->UpdateController(pawnController);
								break;
							}
						}
					}

					break;
				}
				case (SDL_KEYDOWN):
				{
					InputManager::GetInstance()->OnKeyDown(SDL_GetKeyName(ev.key.keysym.sym), InputManager::GetInstance()->ControlledPawn.begin()->first);
					
					break;
				}
				case (SDL_KEYUP):
				{
					InputManager::GetInstance()->OnKeyUp(SDL_GetKeyName(ev.key.keysym.sym), InputManager::GetInstance()->ControlledPawn.begin()->first);
					break;
				}
				case (SDL_CONTROLLERBUTTONDOWN):
				{
					InputManager::GetInstance()->OnButtonDown(ev);
					break;
				}
				case (SDL_CONTROLLERBUTTONUP):
				{
					InputManager::GetInstance()->OnButtonUp(ev);
					break;
				}
			}
		}

		if (InputManager::GetInstance()->ControlledPawn.size())
		{
			// Check keyboard input
			InputManager::GetInstance()->ControlledPawn.begin()->first->CheckKeyState();

			// Check controller input
			InputManager::GetInstance()->OnAxisMotion(ev);
		}

		currentLevel->Update();
		currentLevel->Refresh();
		currentLevel->Draw();
		window->Update();
		
	}
}


Window* GameEngine::GetWindow()
{
	return window;
}

GameEngine* GameEngine::GetInstance()
{
	if (instance == nullptr)
		instance = new GameEngine(); // delete that later

	return instance;
}

int GameEngine::GameWindowWidht()
{
	return myWindowWidth;
}

int GameEngine::GameWindowHeight()
{
	return myWindowHeigth;
}

void GameEngine::ActivateLevelByName(std::string levelName)
{
	currentLevel = levelMap[levelName];
	
}

InputManager* GameEngine::GetInputManager()
{
	return InputManager::GetInstance();
}

Level* GameEngine::GetActiveLevel()
{
	return currentLevel;
}

Level* GameEngine::CreateNewLevel(std::string levelName)
{
	Level* newLevel = new Level(levelName);
	levelMap[levelName] = newLevel;
	return newLevel;
}

void GameEngine::DeleteLevelByName(std::string levelName)
{
	levelMap[levelName]->ClearLevel();
	delete levelMap[levelName];
	
}

class Level* GameEngine::GetLevelByName(std::string levelName)
{
	return levelMap[levelName];
}

b2World* GameEngine::GetWorld()
{
	return world;
}

GameEngine::~GameEngine()
{
	delete InputManager::GetInstance();
	delete textureManager;

	if (window != nullptr)
		delete window;

	if (sdl != nullptr)
		delete sdl;

	std::map<std::string, Level*>::iterator it;
	int count{ 0 };
	for (it = levelMap.begin(); it != levelMap.end(); ++it)
	{
		if(it->second != nullptr)
			delete it->second;
	}
	levelMap.clear();

	delete CollisionListener::GetInstance();

}
