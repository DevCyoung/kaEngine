#include "pch.h"
#include "Entity.h"

namespace engine
{
    Entity::Entity()
        : mName(L"")
        , mID(sID++)
    {                        
    }

    Entity::~Entity()
    {
    }
}