#pragma once
#include "Component.h"
#include "Transform.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>

struct Animation
{
	Animation(std::string textureID, std::string filePath, int rowNumber, int columnNumber, int rowEnd, 
		int columnEnd, int rowStart = 1, int colunmStart = 1, int framesPerSeconds = 2, bool horFlip = false, 
		int layer = 0, bool shouldLoop = true, bool playfoward = true, bool playOnStart = true)
	{
		myTextureID = textureID;
		myFilePath = filePath;
		myColumnNumber = columnNumber;
		myRowNumber = rowNumber;
		myRowEnd = rowEnd;
		myColunmEnd = columnEnd;
		myRowStart = rowStart;
		myColunmStart = colunmStart;
		myFramesPerSeconds = framesPerSeconds;
		flip = horFlip;
		myLayer = layer;
		loop = shouldLoop;
		foward = playfoward;
		startOnplay = playOnStart;
	}
	~Animation()
	{
		//delete texture;
	}

	void Init();
	void SetupAnimation();

	std::string myTextureID{};
	class Texture* texture{ nullptr };
	std::string myFilePath{};
	int myLayer{0};
	int myRowStart{}, myColunmStart{};
	int myRowEnd{}, myColunmEnd{};
	int currentColumn, currentRow;
	int  myColumnNumber{}, myRowNumber{};
	int myFramesPerSeconds{};
	int textureWidth{}, textureHeight{};
	int frameWidth{}, frameHeight{};
	int frameIndex{ 0 };
	std::vector<std::pair<int, int>> frames{};

	bool foward{ true };
	bool startOnplay{ true };
	bool flip{ false };
	bool loop{ true };
};

class Animator : public Component
{
public:
	Animator() { };
	~Animator() override;

	bool Init() override final;
	void Draw() override final;
	void Update() override final;

	void AddAnimation(std::string name, Animation* newAnimation);
	void PlayFromStart(std::string animName, bool loopAnim, bool playFoward = true);

	void AddToAnimationQueue(std::string animName, bool loopAnim, bool playFoward);
	void ClearAnimationQueu();
	inline bool AnimationIsPlaying(){return isActive;}

	inline Animation* GetAnimationByName(std::string name) { return animations[name]; }
	inline Animation* GetCurrentAnimation() { return currentAnimation; }
	inline int GetLayer(){	return currentAnimation->myLayer;}
	
	inline std::pair<int, int> Getframe(){	return currentFrame;}

	

private:

	void PlayFoward();

	Transform* transform {nullptr};
	std::pair<int, int> currentFrame{1,1};
	bool isActive{ true };
	float time{ 0 };
	
	std::map<std::string, Animation*> animations{};
	std::vector<std::tuple<std::string, bool, bool>> animationsQueue{};
	Animation* currentAnimation{};
	
};

