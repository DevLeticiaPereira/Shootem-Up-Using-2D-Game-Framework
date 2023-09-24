#include "GameInput.h"

GameInput* GameInput::sInstance = nullptr;

GameInput::GameInput()
{
	KeyMapping.insert({ "Left", "MoveLeft" });
	KeyMapping.insert({ "Joystick_XAxis_Left", "MoveLeft" });
	KeyMapping.insert ({ "Down", "MoveDown" });
	KeyMapping.insert ({ "Joystick_YAxis_Down", "MoveDown" });
	KeyMapping.insert ({ "Right", "MoveRight" });
	KeyMapping.insert ({ "Joystick_XAxis_Right", "MoveRight" });
	KeyMapping.insert ({ "Up", "MoveUp" });
	KeyMapping.insert ({ "Joystick_YAxis_Up", "MoveUp" });
	KeyMapping.insert ({ "Space", "Attack" });
	KeyMapping.insert ({ "SDL_CONTROLLER_BUTTON_A", "Attack" });

	KeyState.insert({ "Left", false });
	KeyState.insert({ "Down", false });
	KeyState.insert({ "Right", false });
	KeyState.insert({ "Up", false });
	KeyState.insert({ "Space", false });

	ButtonState.insert({ "Joystick_XAxis_Left", false });
	ButtonState.insert({ "Joystick_YAxis_Down", false });
	ButtonState.insert({ "Joystick_XAxis_Right", false });
	ButtonState.insert({ "Joystick_YAxis_Up", false });
	ButtonState.insert({ "SDL_CONTROLLER_BUTTON_A", false });
}

GameInput::~GameInput()
{
	/*std::map<std::string, std::string>::iterator it;
	for (it = KeyMapping.begin(); it != KeyMapping.end(); it++)
	{
		KeyMapping.erase(it);
	}

	std::map<std::string, bool>::iterator it2;
	for (it2 = KeyState.begin(); it2 != KeyState.end(); it2++)
	{
		KeyState.erase(it2);
	}*/
}
