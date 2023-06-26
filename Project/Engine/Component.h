#pragma once
#include "Entity.h"
#include "GameObject.h"

class Component : public Entity
{
	friend class GameObject;

protected:
	Component(const eComponentType type);
public:
	virtual ~Component();
	Component(const Component&) = delete;
	Component& operator=(const Component&) = delete;

public:
	template<typename T>
	T* GetComponentOrNull();
	template<typename T>
	T* GetComponent();	

	GameObject* GetOwner() const { Assert(mOwner, WCHAR_IS_NULLPTR); return mOwner; }
	eComponentType GetType() const { return mType; }

private:
	virtual void initialize();
	virtual void update();
	virtual void lateUpdate();
	virtual void render();

private:
	eComponentType mType;
	GameObject* mOwner;
};

template<typename T>
inline T* Component::GetComponentOrNull()
{
	return mOwner->GetComponentOrNull<T>();
}

template<typename T>
inline T* Component::GetComponent()
{
	T* const component = GetComponentOrNull<T>();

	Assert(component, WCHAR_IS_NULLPTR);
	return component;
}