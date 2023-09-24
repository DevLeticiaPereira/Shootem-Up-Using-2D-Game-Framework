#pragma once

#include <vector>
#include "Entity.h"
#include "Component.h"
#include "Vector2D.h"

constexpr float GRAVITY = 10.0f;

#define UNI_MASS 1.0f;
#define GRAVITY 9.8f;

class Rigidbody : public Component
{
public:
	Rigidbody()
	{
		myMass = UNI_MASS;
		myGravity = GRAVITY;
	};

	virtual ~Rigidbody() = default;

	bool Init() override final;
	void Update() override final;

	inline void SetMass(float mass) { myMass = mass; }
	inline void SetGravity(float gravity) { myGravity = gravity; }

	//Force
	inline void ApplyForce(Vector2D force) { myForce = force; }
	inline void ApplyForceX(float forceX) { myForce.X = forceX; }
	inline void ApplyForceY(float forceY) { myForce.Y = forceY; }
	inline void RemoveForce() { myForce = Vector2D(0, 0); }

	//Frictions
	inline void ApplyFriction(Vector2D friction) { myFriction = friction; }
	inline void RemoveFriction(Vector2D friction) { myFriction= Vector2D(0, 0); }

	float myGravity{};
private:

	float myMass{};
	//float myGravity{};

	Vector2D myForce{};
	Vector2D myFriction{};

	Transform* transform{ nullptr };
	Vector2D myVelocity{};
	Vector2D myAcceleration{};

	//drag
	//vector 2D force
	//velocity

	
};