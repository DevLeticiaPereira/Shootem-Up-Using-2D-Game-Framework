#pragma once
#include "GameEngine.h"
#include "Pawn.h"
#include <vector>
#include <unordered_map>
#include "Companion.h"

class Spaceship : public Pawn
{
public:
	Spaceship();
	~Spaceship() 
	{
		delete gameInput;
	};

	enum Movement { move_right, move_left, move_up, move_down };

	int maxHealth{};

	void ApplyShield(int shieldValue);
	void ApplyDamage(int damageReceived);
	void ChangeBulletLevel(bool willIncrease);
	void RemoveCompanion(float posX, float posY, Companion* companion);

	void WasHit(Entity* collidedObject) override;


private:
	float moveSpeed{ 300.0f };
	float uniform{ 0.7071f };
	float spaceshipXDir{};
	float lastPosY{};
	float time{};
	float bulletDeltaTime{0.1f};
	float bulletCoolDown{0.15f};
	float colliderHeight{};
	float colliderWidth{};

	int maxLives{};
	int currentLives{};
	int health{};
	int currentCompanions{};
	int maxCompanions{};
	int bulletLevel{};
	int bulletMinLevel{};
	int bulletMaxLevel{};

	int animDir{0};
	class Animator myAnimator{};
	Animation* moveUp{};
	Animation* moveDown{};
	Animation* idle{};

	

	class GameInput* gameInput;

	void OnKeyDown(std::string keycode) override;
	void OnKeyUp(std::string key) override;
	void OnButtonDown(std::string button) override;
	void OnButtonUp(std::string button) override;
	void OnAxisChange(float axisValue, bool Yaxis) override;
	void Init() override final;
	void Update() override final;
	void Move();
	void Attack();
	void CheckKeyState() override;
	void IncreaseCompanionCount();
	void DecreaseCompanionCount();
	bool HasMaxCompanions();
	void SetupFireEffects();

	void ShipAnimation();

	std::map<std::string, Entity*> fireEfx;

	std::pair<Vector2D, Companion*> companionPos1{};
	std::pair<Vector2D, Companion*> companionPos2{};

	std::map<std::string, bool> KeyboardKeystate;
	std::map<std::string, bool> GamepadButtonstate;
};