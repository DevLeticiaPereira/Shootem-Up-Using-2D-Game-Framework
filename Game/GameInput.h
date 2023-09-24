#pragma once
#include <iostream>
#include <map>

#ifndef INPUTMANAGER_M
#define INPUTMANAGER_M

class GameInput
{
public:
	GameInput();
	~GameInput();

	// Create a singleton
	static GameInput* GetInstance() { return sInstance = (sInstance != nullptr) ? sInstance : new GameInput(); }

	std::map<std::string, std::string> KeyMapping{};

	std::map<std::string, bool> KeyState{};

	std::map<std::string, bool> ButtonState{};

	std::map<std::string, bool> GetKeyState() { return KeyState; }

	std::map<std::string, bool> GetButtonState() { return ButtonState; }

private:
	
	static GameInput* sInstance;
};

#endif