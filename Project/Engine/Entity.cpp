#include "pch.h"
#include "Entity.h"

namespace engine
{
    Entity::Entity()
        : mName(L"None")
        , mID(sID++)
    {                        
    }

    Entity::~Entity()
    {
    }
}
