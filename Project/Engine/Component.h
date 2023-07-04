#pragma once
#include "Entity.h"
#include "GameObject.h"

class Component : public Entity
{
	friend class GameObject;

protected:
	Component(const eComponentType COMPONENT_TYPE);
public:
	virtual ~Component();
	Component(const Component&) = delete;
	Component& operator=(const Component&) = delete;

public:
	template<typename T>
		requires (is_component_type<T>::value)
	T* GetComponentOrNull() const;		
	template<typename T>
		requires (is_component_type<T>::value)
	T* GetComponent() const;	

	GameObject* GetOwner() const { Assert(mOwner, WCHAR_IS_NULLPTR); return mOwner; }
	eComponentType GetType() const { return mType; }

private:
	virtual void initialize();
	virtual void update();
	virtual void lateUpdate();	

private:
	eComponentType mType;
	GameObject* mOwner;
};

template<typename T>
	requires (is_component_type<T>::value)
inline T* Component::GetComponentOrNull() const
{
	return mOwner->GetComponentOrNull<T>();
}

template<typename T>
	requires (is_component_type<T>::value)
inline T* Component::GetComponent() const
{
	T* const component = GetComponentOrNull<T>();
	Assert(component, WCHAR_IS_NULLPTR);

	return component;
}


