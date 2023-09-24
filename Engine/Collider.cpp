#include "Collider.h"
#include "Rigidbody.h"
#include "Entity.h"
#include "GameEngine.h"
#include <box2d/box2d.h>

Collider::~Collider()
{
	world->DestroyBody(body);
}

bool Collider::Init()
{
	transform = &entity->GetComponent<Transform>();
	world = GameEngine::GetInstance()->GetWorld();
	return true;
}

void Collider::Update()
{
	transform = &entity->GetComponent<Transform>();
}

void Collider::AddAttributes(std::string id, Entity* entity, BodyType bodyType, float objectLocationX, float objectLocationY, float colliderWidth, float colliderHeight, bool isBullet, float gravity)
{
	colliderId = id;

	b2BodyDef objectBodyDef;

	switch (bodyType)
	{
		case (BodyType::dynamicBody):
			objectBodyDef.type = b2_dynamicBody;
			break;

		case(BodyType::kinematicBody):
			objectBodyDef.type = b2_kinematicBody;
			break;

		case(BodyType::staticBody):
			objectBodyDef.type = b2_staticBody;
			break;
	}

	objectBodyDef.position.Set(objectLocationX, objectLocationY);
	objectBodyDef.userData.pointer = (uintptr_t)entity;
	objectBodyDef.bullet = isBullet;

	body = GameEngine::GetInstance()->GetWorld()->CreateBody(&objectBodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(colliderWidth / 2.0f, colliderHeight / 2.0f);
	colliderHalfWidth = colliderWidth / 2.0f;
	colliderHalfHeight = colliderHeight / 2.0f;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	fixtureDef.density = 1.0f;
	fixtureDef.isSensor = true;

	body->CreateFixture(&fixtureDef);
	body->SetGravityScale(gravity);
}

void Collider::SetPosition(float objectLocationX, float objectLocationY)
{
	b2Vec2 newPos;
	newPos.x = objectLocationX + colliderHalfWidth;
	newPos.y = objectLocationY + colliderHalfHeight;
	body->SetTransform(newPos, 0.0f);
}

void Collider::SetVelocity(Vector2D newVelocity)
{
	b2Vec2 newVel;
	newVel.x = newVelocity.X;
	newVel.y = newVelocity.Y;
	body->SetLinearVelocity(newVel);
}

void Collider::SetBullet(bool isBullet)
{
	body->SetEnabled(isBullet);
}

Vector2D Collider::GetPosition()
{
	Vector2D returnPosition;
	b2Vec2 bodyPos;
	bodyPos = body->GetPosition();

	returnPosition.X = bodyPos.x - colliderHalfWidth;
	returnPosition.Y = bodyPos.y - colliderHalfHeight;

	return returnPosition;
}
