#include "Animator.h"
#include "TextureManager.h"
#include "Entity.h"

#include <string>
#include <vector>
#include <iostream>
#include "SDL.h"


void Animation::Init()
{
	if (TextureManager::GetInstance()->GetTexture(myTextureID) == nullptr)
		texture = TextureManager::GetInstance()->LoadTexture(myTextureID, myFilePath);
	else
		texture = TextureManager::GetInstance()->GetTexture(myTextureID);

	frameWidth = static_cast<int>(texture->GetWidth() / myColumnNumber);
	frameHeight = static_cast<int>(texture->GetHeight() / myRowNumber);
	currentColumn = myColunmStart;
	currentRow = myRowStart;

	SetupAnimation();

	if (!foward)
		frameIndex = (static_cast<int>(frames.size()) - 1);
	else
		frameIndex = 0;

}

void Animation::SetupAnimation()
{
	for (int row = myRowStart; row <= myRowNumber; ++row)
	{
		for (int col = 1; col <= myColumnNumber; ++col)
		{
			if (row < myRowStart || row > myRowEnd)
			{
				break;
			}
			else if (row == myRowEnd && col > myColunmEnd)
			{
				break;
			}
			else if (row == myRowStart && col < myColunmStart)
			{
				continue;
			}
			std::pair<int, int> newFrame{ row, col };
		
			frames.push_back(newFrame);
			//std::cout << "row " << newFrame.first << " column " << newFrame.second << std::endl;
		}
	}
}

Animator::~Animator()
{
	if (animations.size() > 0)
	{
		std::map<std::string, Animation*>::iterator it;

		for (it = animations.begin(); it != animations.end(); ++it)
		{
			delete it->second;
		}
		animations.clear();
	}
}

bool Animator::Init()
{
	transform = &entity->GetComponent<Transform>();

	return true;
}

void Animator::Draw()
{
	TextureManager::GetInstance()->DrawFrame(currentAnimation->myTextureID, transform, currentFrame.first, currentFrame.second, 
				currentAnimation->myRowNumber, currentAnimation->myColumnNumber, transform->myRotation, currentAnimation->flip);
}


void Animator::Update()
{
	transform = &entity->GetComponent<Transform>();
	if(currentAnimation != nullptr)
	{ 
		if (isActive)
		{
			time += GameEngine::GetInstance()->GetDeltatime();
			
			if (time > (1.0f / currentAnimation->myFramesPerSeconds))
			{
				PlayFoward();
				time = 0;
			}

			currentFrame = currentAnimation->frames.at(currentAnimation->frameIndex);
		}	
	}
}

void Animator::AddAnimation(std::string name, Animation* newAnimation)
{
	animations[name] = newAnimation;
	animations[name]->Init();

	if (animations.size() == 1)
   		currentAnimation = animations[name];
}

void Animator::PlayFoward()
{
	if (currentAnimation->foward)
	{
		if (currentAnimation->frameIndex < (currentAnimation->frames.size() - 1))
		{
			++currentAnimation->frameIndex;
		}
		else
		{
			if (currentAnimation->loop)
			{
				currentAnimation->frameIndex = 0;
			}
			else
			{
				if (animationsQueue.size() > 0)
				{
					std::tuple<std::string, bool, bool> nextAnim{};
					nextAnim = animationsQueue.front();
					animationsQueue.erase(animationsQueue.begin());
					PlayFromStart(std::get<0>(nextAnim), std::get<1>(nextAnim), std::get<2>(nextAnim));
				}
				else
					isActive = false;
			}
		}
	}
	else
	{
		if (currentAnimation->frameIndex > 0)
		{
			--currentAnimation->frameIndex;
		}
		else
		{
			if (currentAnimation->loop)
			{
				currentAnimation->frameIndex = static_cast<int>(currentAnimation->frames.size() - 1);
			}
			else
			{
				if (animationsQueue.size() > 0)
				{
					std::tuple<std::string, bool, bool> nextAnim{};
					nextAnim = animationsQueue.front();
					animationsQueue.erase(animationsQueue.begin());
					PlayFromStart(std::get<0>(nextAnim), std::get<1>(nextAnim), std::get<2>(nextAnim));
				}
				else
					isActive = false;
			}
		}
	}
}

void Animator::PlayFromStart(std::string animName, bool loopAnim, bool playFoward)
{
	currentAnimation = animations[animName];

	currentAnimation->foward = playFoward;

	if (currentAnimation->foward)
	{
		currentAnimation->frameIndex = 0;
	}
	else
	{
		currentAnimation->frameIndex = static_cast<int>(currentAnimation->frames.size() - 1);
	}

	currentAnimation->loop = loopAnim;

	isActive = true;
}

void Animator::AddToAnimationQueue(std::string animName, bool loopAnim, bool playFoward)
{
	std::tuple<std::string, bool, bool> anim{ animName, loopAnim, playFoward };
	animationsQueue.push_back(anim);
}

void Animator::ClearAnimationQueu()
{
	animationsQueue.clear();
}
