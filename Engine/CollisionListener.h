#pragma once
#include <box2d/box2d.h>

#ifndef COLLISIONLISTENER_M
#define COLLISIONLISTENER_M

class CollisionListener : public b2ContactListener
{
public:
    CollisionListener() {};

    // Create a singleton
    static CollisionListener* GetInstance() { return sInstance = (sInstance != nullptr) ? sInstance : new CollisionListener(); }

    void BeginContact(b2Contact* contact);

    ~CollisionListener() {};

private:
    static CollisionListener* sInstance;
};

#endif