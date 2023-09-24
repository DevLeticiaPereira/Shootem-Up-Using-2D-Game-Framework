// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "GameEngine.h"
#include "Spaceship.h"
#include "Entity.h"
#include <Vector2D.h>
#include "Spawner.h"
#include "level.h"
#include "loner.h"
#include "rusher.h"
#include "UIManager.h"
#include "BackGround.h"

int main(int argc, char** argv)
{

    GameEngine::GetInstance()->init("Xennon Clone.", 640, 480);

    //set up do level

    Animation* anim1 = new Animation("background", "assets/galaxy2.bmp", 1, 1, 1, 1, 1, 1, 2, false, 1, false);
    Animation* anim2 = new Animation("background2", "assets/galaxy2.bmp", 1, 1, 1, 1, 1, 1, 2, true, 1, false);

    BackGround* bg1 = new BackGround(anim1,"background", - static_cast<float>(GameEngine::GetInstance()->GameWindowWidht() / 2), static_cast<float>(GameEngine::GetInstance()->GameWindowHeight() / 2), 1);
    BackGround* bg2 = new BackGround(anim2,"background2", static_cast<float>(GameEngine::GetInstance()->GameWindowWidht() / 2), static_cast<float>(GameEngine::GetInstance()->GameWindowHeight() / 2), 1);


    Spawner* spawner = new Spawner;

    Spaceship* currentPlayer = new Spaceship;
    currentPlayer->GetComponent<Transform>().myPosition.X = static_cast<float>(GameEngine::GetInstance()->GameWindowWidht() / 2);
    currentPlayer->GetComponent<Transform>().myPosition.Y = static_cast<float>(GameEngine::GetInstance()->GameWindowHeight() / 2);

    spawner->SetPlayerReference(currentPlayer);
    
    //não é necessario dar delete dos "Entities" criados. O nível cuida disto :)

    UIManager::GetInstance()->DrawUI();

    //newEnt2->AddGroup(GameEngine::GetInstance()->groupUI);

    GameEngine::GetInstance()->start();

    // game logic
    delete UIManager::GetInstance();
    delete GameEngine::GetInstance();
    
    return 0;
}
