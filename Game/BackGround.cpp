#include "BackGround.h"

BackGround::BackGround(Animation* anim, std::string animName, float posX, float posY, float velocity)
{
    windowWidth = GameEngine::GetInstance()->GameWindowWidht();
    windowHeight = GameEngine::GetInstance()->GameWindowHeight();

    AddComponent<Animator>();
    myAnimName = animName;
    animation = anim;
   
    paralaxVel = velocity;

    GetComponent<Transform>().myPosition.X = posX;
    GetComponent<Transform>().myPosition.Y = posY;
}

BackGround::~BackGround()
{

}

void BackGround::Init()
{
    Entity::Init();

    GetComponent<Animator>().AddAnimation(myAnimName, animation);

}

void BackGround::Update()
{
    Entity::Update();

    GetComponent<Transform>().myPosition.X -= paralaxVel;

    if (GetComponent<Transform>().myPosition.X < - GetComponent<Animator>().GetCurrentAnimation()->frameWidth / 2)
    {
        GetComponent<Transform>().myPosition.X = windowWidth - 1 + GetComponent<Animator>().GetCurrentAnimation()->frameWidth / 2;
    }
}


