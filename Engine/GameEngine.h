#pragma once
#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <vector>
#include <string>
#include <map>

class GameEngine
{
public:
	void init(std::string windowTitle, int windowWidth, int windowHeight);
	void start();

	class Window* GetWindow();
	static GameEngine* GetInstance();
	int GameWindowWidht();
	int GameWindowHeight();

	class InputManager* GetInputManager();
	 
	void ActivateLevelByName(std::string levelName);
	class Level* GetActiveLevel();
	class Level* CreateNewLevel(std::string levelName);
	void DeleteLevelByName(std::string levelName);
	class Level* GetLevelByName(std::string levelName);

	inline float GetDeltatime() { return deltaTime; }
	inline bool IsRunning(){ return isRunning; }

	/*enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupColliders,
		groupProjectiles,
		groupBackground,
		groupUI,
	};*/

	GameEngine();

	~GameEngine();

	class b2World* GetWorld();

private:
	int prevTime;
	int currentTime;
	float deltaTime;
	bool isRunning{ false };
	int myWindowWidth{};
	int myWindowHeigth{};
	
	static GameEngine* instance;
	class TextureManager* textureManager{ nullptr };
	class SDLWrapper* sdl{ nullptr };
	class b2World* world;
	class Window* window{ nullptr };
	class Level* currentLevel{ nullptr };
	class Level* defaultLevel{ nullptr };
	std::map<std::string, class Level*> levelMap;
};

#endif //