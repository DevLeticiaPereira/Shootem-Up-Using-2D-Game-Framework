#include "UIManager.h"
#include <fstream>
#include <iostream>
#include "Transform.h"

UIManager* UIManager::sInstance{ nullptr };

UIManager::UIManager()
{
    
}


void UIManager::DrawIcons(std::string textureID, std::string filePath, float x, float y, int layer, std::vector<Icon*>& icons)
{
    Icon* newIcon = new Icon(textureID, filePath, x, y, true, 1, 1, 1, 1, layer);

    icons.push_back(newIcon);
}

void UIManager::SetMaxLives(int maxLives)
{
    playerLives = maxLives;
    DrawLives(playerLives);
}

void UIManager::ScoreUi(Vector2D position, std::string text)
{
    std::string enemyScore = text;
    Text* EnemyPoints = new Text(enemyScore, TextType::small, 0, position.X, position.Y + 32, 10);
    EnemyPoints->SetTimerForDestruction(0.75f);
    EnemyPoints->SetMoveUp(2);
}

void UIManager::ResetPlayerScore()
{
    playerScore = 0;
    UpdateScore(0);
}

void UIManager::DrawUI()
{
    DrawTitles();
    DrawScore("0000000000");
    DrawHighScore(GetHiScore());
    DrawHealthBar();
}

void UIManager::UpdateScore(int newScore)
{ 
    scoreText->Destroy();
    playerScore += newScore;

    std::string updatedScore = std::to_string(playerScore);

    int charNumber = updatedScore.size();
    int zeros = 10 - charNumber;
    std::string zerosString{};

    for (int i = 0; i < zeros;++i)
    {
        zerosString.append("0");
    }

    std::string finalScore = zerosString.append(updatedScore);

    DrawScore(finalScore);

    if (playerScore > hiScore)
    {
        UpdateHighScore(playerScore);
    }
}

void UIManager::UpdateHighScore(int hiScore)
{
    hiScoreText->Destroy();

    SaveScore(hiScore);
    DrawHighScore(hiScore);
}

void UIManager::UpdateHealth(int maxHealth, int health)
{
    float percentage = (float)health / (float)maxHealth;

    if (percentage < 0)
    {
        percentage = 0;
    }

    int healthWidth = healthBar->GetComponent<SpriteComponent>().GetWidth();

    healthBar->GetComponent<Transform>().myScale.X = percentage;

    if (percentage > 0.7)
    {
        healthBar->GetComponent<SpriteComponent>().SetFilterColor(0.0f, 0.9f, .0f, 0.8f);
    }
    else if (percentage <= 0.7 && percentage > 0.4)
    {
        healthBar->GetComponent<SpriteComponent>().SetFilterColor(1.0f, 1.0f, 0.0f, 0.8f);
    }
    else if (percentage <= 0.4)
    {
        healthBar->GetComponent<SpriteComponent>().SetFilterColor(0.9f, 0.0f, .0f, 0.8f);
    }
}

void UIManager::UpdateLives(int lifeNumber)
{
    for (Icon* lifeIcon : lives)
    {
        lifeIcon->Destroy();
    }

    lives.clear();

    DrawLives(lifeNumber);
}

void UIManager::SaveScore(int newHiScore)
{
    std::ofstream hiScoreFile;
    hiScoreFile.open("HighScore.txt");

    // Check for error
    if (hiScoreFile.fail())
    {
        std::cout << "Error openning file." << std::endl;
        exit(1);
    }

    hiScoreFile << newHiScore;
}

int UIManager::GetHiScore()
{
    std::ifstream hiScoreFile;
    hiScoreFile.open("HighScore.txt");

    // Check for error
    if (hiScoreFile.fail())
    {
        std::cout << "Error openning file." << std::endl;
        exit(1);
    }

    hiScoreFile >> hiScore;


    return hiScore;
}

void UIManager::DrawTitles()
{
    int hiPosX = (GameEngine::GetInstance()->GameWindowWidht() / 2) - 40.f;
    int hiPosY = (GameEngine::GetInstance()->GameWindowHeight() / 2) + 220.f;
    Text* hiScoreTitle = new Text("Hi Score", TextType::small, 0, hiPosX, hiPosY, 10);

    int scoreTitlePosX = (GameEngine::GetInstance()->GameWindowWidht() / 2) - 300.f;
    int scoreTitlePosY = (GameEngine::GetInstance()->GameWindowHeight() / 2) + 220.f;
    Text* playerTitle = new Text("Player One", TextType::small, 0, scoreTitlePosX, scoreTitlePosY, 10);
}

void UIManager::DrawScore(std::string currentScore)
{
    // Draw the high score
    int scorePosX = (GameEngine::GetInstance()->GameWindowWidht() / 2) - 300.f;
    int scorePosY = (GameEngine::GetInstance()->GameWindowHeight() / 2) + 200.f;
   
    scoreText = new Text(currentScore, TextType::big, 0, scorePosX, scorePosY, 10);
}

void UIManager::DrawHighScore(int hiScore)
{
    // Draw the high score
    hiScorePosX = (GameEngine::GetInstance()->GameWindowWidht() / 2) - 47.f;
    hiScorePosY = (GameEngine::GetInstance()->GameWindowHeight() / 2) + 205.f;

    std::string currentHiScore = std::to_string(hiScore);

    int charNumber = currentHiScore.size();
    int zeros = 10 - charNumber;
    std::string zerosString{};

    for (int i = 0; i < zeros; ++i)
    {
        zerosString.append("0");
    }

    std::string finalHiScore = zerosString.append(currentHiScore);

    hiScoreText = new Text(finalHiScore, TextType::small, 0, hiScorePosX, hiScorePosY, 10);
}

void UIManager::DrawLives(int totalLives)
{
    float posX = 30.f;
    float posY = 60.f;

    for (int i = 0; i < totalLives; ++i)
    {        
        DrawIcons("icon", "assets/PULife.bmp", posX, posY, 10, lives);

        // now advance cursors for the next character
        posX += 40.f;
    }    
}

void UIManager::DrawHealthBar()
{
   healthBar = new Icon("healthBar", "assets/healthBar.bmp", barPosition.X - 80.f, barPosition.Y, false, 1, 1, 1, 1, 9);
   Icon* healthBorder = new Icon("healthBorder", "assets/healthBorder.bmp", barPosition.X, barPosition.Y, false, 1, 1, 1, 1, 10);
   healthBar->GetComponent<SpriteComponent>().SetFilterColor(0.0f, 0.9f, 0.0f, 0.8f);
   staticIcons.push_back(healthBorder);
}
