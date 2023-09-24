#pragma once

#ifndef INPUTMANAGER_M
#define INPUTMANAGER_M

#include <iostream>
#include <map>
#include <vector>
#include "SDL.h"
#include "SDL_gamecontroller.h"

class InputManager
{

public:
	InputManager();

	~InputManager();

	int numControllers;

	// Create a singleton
	static InputManager* GetInstance() { return sInstance = (sInstance != nullptr) ? sInstance : new InputManager(); }

	void AddPawn(class Pawn* pawn);

	// Map the new connected controller
	void MapNewController(int controllerIndex);

	void OnKeyDown(std::string keycode, class Pawn* currentPlayer);

	void OnKeyUp(std::string keycode, class Pawn* currentPlayer);

	void OnButtonDown(SDL_Event gamepadEvent);

	void OnButtonUp(SDL_Event gamepadEvent);

	void OnAxisMotion(SDL_Event gamepadEvent);

	// Pawn and their respective controller
	std::map<Pawn*, SDL_GameController*> ControlledPawn{};

	// Controller and corresponding index
	std::map<int, SDL_GameController*> ControllerIndex{};

	std::map<Pawn*, SDL_GameController*> GetControlledPawn() { return ControlledPawn; }

	// Update the pawn and controller relation
	void UpdateController(std::map<Pawn*, SDL_GameController*> updatedControllerMap) { ControlledPawn = updatedControllerMap; }

	void UpdateControllerIndex(std::map<int, SDL_GameController*> updatedIndex) { ControllerIndex = updatedIndex; };

private:
	static InputManager* sInstance;
	const Uint8* keyState;
	float joystickDeadZone = 800.0f;
};

#endif // INPUTMANAGER_M#pragma once
