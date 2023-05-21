#pragma once
#include "Engine.h"

namespace engine
{
    class Entity
    {
    public:
        Entity();        
        virtual ~Entity();

    public:
        void SetName(const std::wstring& name) { mName = name; }
        const std::wstring& GetName() const { return mName; }

    private:
        std::wstring mName;
        UINT64 mID;
    };
}
