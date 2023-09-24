#pragma once

//#ifndef UIMANAGER_M
//#define UIMANAGER_M

#include <string>
#include <vector>
#include <map>
#include "Icon.h"
#include "Text.h"

enum class CharacterType { small, big };

class UIManager 
{
public:

	UIManager();
	~UIManager() {};

	void DrawUI();
	void UpdateScore(int newScore);
	void UpdateHighScore(int hiScore);
	void UpdateHealth(int maxHealth, int health);
	void UpdateLives(int lifeNumber);

	static UIManager* GetInstance() { return sInstance = (sInstance != nullptr) ? sInstance : new UIManager(); }
	void DrawIcons(std::string textureID, std::string filePath, float x, float y, int layer, std::vector<Icon*>& icons);
	void SetMaxLives(int maxLives);
	void ScoreUi(Vector2D position, std::string text);
	void ResetPlayerScore();

private:

	static UIManager* sInstance;

	int playerScore = {};
	int hiScore = {};
	int scorePosX = {};
	int scorePosY = {};
	int hiScorePosX = {};
	int hiScorePosY = {};
	int playerLives = {};

	void SaveScore(int newHiScore);
	int GetHiScore();

	void DrawTitles();
	void DrawScore(std::string currentScore);
	void DrawHighScore(int hiScore);
	void DrawLives(int totalLives);
	void DrawHealthBar();

	Icon* healthBar{};
	Text* hiScoreText{};
	Text* scoreText{};
	Vector2D barPosition{ 100.f, 25.f};
	std::vector<Icon*> staticIcons{};
	std::vector<Icon*> lives{};

	std::map<Text*, int> enemyScoreText;
};

//#endif // UIMANAGER_M