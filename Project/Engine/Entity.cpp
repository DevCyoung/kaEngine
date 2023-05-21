#include "Entity.h"

namespace engine
{
    Entity::Entity()
        : mName(L"")
        , mID(0)
    {
        mID = reinterpret_cast<UINT64>(this);        
    }

    Entity::~Entity()
    {
    }
}