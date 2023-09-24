#include "CollisionListener.h"
#include "Entity.h"
#include "Pawn.h"
#include <iostream>

CollisionListener* CollisionListener::sInstance{ nullptr };

    void CollisionListener::BeginContact(b2Contact* contact)
    {
        void* userData1 = (void*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;

        void* userData2 = (void*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;

        Entity* object1 = static_cast<Entity*>(userData1);

        Entity* object2 = static_cast<Entity*>(userData2);

        if (object1)
        {
            object1->WasHit(object2);
        }

        if (object2)
        {
            object2->WasHit(object1);
        }
    }




