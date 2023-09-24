#pragma once
#include "Component.h"
#include "Transform.h"
#include <vector>
#include <string>

class Collider : public Component
{
public:
	Collider() {};
	~Collider();

	enum class BodyType { dynamicBody, kinematicBody, staticBody };

	bool Init() override final;

	void Update() override final;

	void AddAttributes(std::string id, Entity* entity, BodyType bodyType, float objectLocationX, float objectLocationY, float colliderWidth, float colliderHeight, bool isBullet, float gravity);

	void SetPosition(float objectLocationX, float objectLocationY);

	void SetVelocity(Vector2D newVelocity);

	void SetBullet(bool isBullet);

	float GetColliderHalfWidth() { return colliderHalfWidth; }

	float GetColliderHalfHeight() { return colliderHalfHeight; }

	std::string GetId() { return colliderId; }

	Vector2D GetPosition();

	float colliderHalfWidth{ 0 };
	float colliderHalfHeight{ 0 };
private:
	std::string colliderId {};;
	class b2Body* body {};
	class b2World* world{};
	Transform* transform{ nullptr };
};