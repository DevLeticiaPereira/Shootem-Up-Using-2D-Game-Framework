#include "Rigidbody.h"

bool Rigidbody::Init()
{
    transform = &entity->GetComponent<Transform>();
    return false;
}

void Rigidbody::Update() // pess on the delta time?
{
    myAcceleration.X = (myForce.X + myFriction.X) / myMass;
    myAcceleration.Y = (myGravity + myForce.Y) / myMass;
    myVelocity = myAcceleration;
    transform->myPosition.X += myVelocity.X;
    transform->myPosition.Y += myVelocity.Y;
    // myVelocitty = myAcceleration*dt;
    // myPosition = myVelocity*dt;


}
