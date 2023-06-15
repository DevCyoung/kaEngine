#pragma once

namespace engine
{
    class Entity
    {
    public:
        Entity();        
        virtual ~Entity();
        void SetName(const std::wstring& name) { mName = name; }
        const std::wstring& GetName() const { return mName; }

    private:
        inline static UINT sID = 0;
        std::wstring mName;
        UINT mID;
    };
}