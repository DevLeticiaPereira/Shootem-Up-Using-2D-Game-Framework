#include <SDL.h>
#include <iostream>
#include "Pawn.h"
#include "InputManager.h"

InputManager* InputManager::sInstance{ nullptr };

InputManager::InputManager()
{
	class Pawn* pawn = nullptr;
	numControllers = 0;
	keyState = SDL_GetKeyboardState(NULL);
}

void InputManager::AddPawn(Pawn* pawn)
{
	ControlledPawn.insert({ pawn, nullptr });
}

void InputManager::MapNewController(int controllerIndex)
{
	SDL_GameController* controller;

	if (SDL_IsGameController(controllerIndex)) {
		char* mapping;
		std::cout << "Index '" << controllerIndex << "' is a compatible controller, named '" <<
			SDL_GameControllerNameForIndex(controllerIndex) << "'" << std::endl;
		controller = SDL_GameControllerOpen(controllerIndex);
		mapping = SDL_GameControllerMapping(controller);
		std::cout << "Controller " << controllerIndex << " is mapped as \"" << mapping << std::endl;
		SDL_free(mapping);
		SDL_GameControllerUpdate();
	}
	else {
		std::cout << "Index '" << controllerIndex << "' is not a compatible controller." << std::endl;
	}
}

void InputManager::OnKeyDown(std::string keycode, Pawn* currentPlayer)
{
	currentPlayer->OnKeyDown(keycode);
}

void InputManager::OnKeyUp(std::string keycode, Pawn* currentPlayer)
{
	currentPlayer->OnKeyUp(keycode);
}

void InputManager::OnButtonDown(SDL_Event gamepadEvent)
{
	Pawn* currentPlayer = nullptr;
	SDL_GameController* controller = nullptr;

	std::map<Pawn*, SDL_GameController*>::iterator it;
	for (it = ControlledPawn.begin(); it != ControlledPawn.end(); ++it)
	{
		if (it->second == SDL_GameControllerFromInstanceID(gamepadEvent.cdevice.which))
		{
			currentPlayer = it->first;
			controller = it->second;

			break;
		}
	}

	if (currentPlayer)
	{
		if (gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_A)
		{
			currentPlayer->OnButtonDown("SDL_CONTROLLER_BUTTON_A");
		}

		if (gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_B)
		{
			currentPlayer->OnButtonDown("SDL_CONTROLLER_BUTTON_B");
		}

		if (gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_X)
		{
			currentPlayer->OnButtonDown("SDL_CONTROLLER_BUTTON_X");
		}

		if (gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_Y)
		{
			currentPlayer->OnButtonDown("SDL_CONTROLLER_BUTTON_Y");
		}
	}
}

void InputManager::OnButtonUp(SDL_Event gamepadEvent)
{
	Pawn* currentPlayer = nullptr;
	SDL_GameController* controller = nullptr;

	std::map<Pawn*, SDL_GameController*>::iterator it;
	for (it = ControlledPawn.begin(); it != ControlledPawn.end(); ++it)
	{
		if (it->second == SDL_GameControllerFromInstanceID(gamepadEvent.cdevice.which))
		{
			currentPlayer = it->first;
			controller = it->second;

			break;
		}
	}

	if (currentPlayer)
	{
		if (gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_A)
		{
			currentPlayer->OnButtonUp("SDL_CONTROLLER_BUTTON_A");
		}

		if (gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_B)
		{
			currentPlayer->OnButtonUp("SDL_CONTROLLER_BUTTON_B");
		}

		if (gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_X)
		{
			currentPlayer->OnButtonUp("SDL_CONTROLLER_BUTTON_X");
		}

		if (gamepadEvent.cbutton.button == SDL_CONTROLLER_BUTTON_Y)
		{
			currentPlayer->OnButtonUp("SDL_CONTROLLER_BUTTON_Y");
		}
	}

}

void InputManager::OnAxisMotion(SDL_Event gamepadEvent)
{
	Pawn* currentPlayer = nullptr;

	if (gamepadEvent.type == SDL_JOYAXISMOTION && (ControlledPawn.size() != 0))
	{
		std::map<Pawn*, SDL_GameController*>::iterator it;
		for (it = ControlledPawn.begin(); it != ControlledPawn.end(); ++it)
		{
			if (it->second == SDL_GameControllerOpen(gamepadEvent.cdevice.which))
			{
				currentPlayer = it->first;

				break;
			}
		}
				
		if (gamepadEvent.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX)
		{
			float axisValue = gamepadEvent.caxis.value;
			if (axisValue < 0 )
			{
				axisValue /= 32768;
				currentPlayer->OnAxisChange(axisValue, false);
			}
			else
			{
				axisValue /= 32767;
				currentPlayer->OnAxisChange(axisValue, false);
			}
		}
		if (gamepadEvent.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY)
		{
			float axisValue = gamepadEvent.caxis.value;
			if (axisValue < 0)
			{
				axisValue /= 32768;
				currentPlayer->OnAxisChange(axisValue, true);
			}
			else
			{
				axisValue /= 32767;
				currentPlayer->OnAxisChange(axisValue, true);
			}
		}
	}
}

InputManager::~InputManager()
{
	
	std::map<Pawn*, SDL_GameController*>::iterator it;
	for (it = ControlledPawn.begin(); it != ControlledPawn.end(); ++it)
	{
		SDL_GameControllerClose(it->second);
	}

	std::map<int, SDL_GameController*>::iterator it2;
	for (it2 = ControllerIndex.begin(); it2 != ControllerIndex.end(); ++it2)
	{
		SDL_GameControllerClose(it2->second);
	}
}