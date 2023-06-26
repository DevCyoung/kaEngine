#pragma once
#include "Entity.h"
#include "GameObject.h"

//class Gameobject;

class Component : public Entity
{
	friend class GameObject;

public:
	Component(const eComponentType type);
	virtual ~Component();
	Component(const Component&) = delete;
	Component& operator=(const Component&) = delete;

public:
	GameObject* GetOwner() const { Assert(mOwner, WCHAR_IS_NULLPTR); return mOwner; }
	eComponentType GetType() const { return mType; }

	template<typename T>
	T* GetComponent()
	{
		T* const component = mOwner->GetComponent<T>();
		return component;
	}

	template<typename T>
	T* GetComponentOrNull()
	{
		return mOwner->GetComponentOrNull<T>();
	}

private:
	virtual void initialize();
	virtual void update();
	virtual void lateUpdate();
	virtual void render();

private:
	eComponentType mType;
	GameObject* mOwner;
};