#include "pch.h"
#include "Entity.h"

namespace engine
{

    UINT64 Entity::sID = 0;

    Entity::Entity()
        : mName(L"")
        , mID(sID++)
    {                        
    }

    Entity::~Entity()
    {
    }
}