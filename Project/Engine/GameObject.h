#pragma once
#include "Entity.h"
#include "ComponentTrait.h"
#include "EnumComponent.h"
#include "EnumLayer.h"

class ScriptComponent;

class GameObject : public Entity
{
	friend class Layer;
	friend class Scene;

public:
	enum class eState
	{
		Active,
		Destroy,
	};

	GameObject();
	virtual ~GameObject();
	GameObject(const GameObject&) = delete;
	GameObject& operator=(const GameObject&) = delete;

public:
	template<typename T>
		requires (is_component_type<T>::value)
	T* GetComponentOrNull() const;
	template<typename T>
		requires (is_component_type<T>::value)
	T* GetComponent() const;
	Component* GetComponentOrNull(const eComponentType componentType) const;
	ScriptComponent* GetComponentOrNull(const eScriptComponentType scriptComponentType) const;

	template<typename T>
		requires (is_component_type<T>::value)
	void AddComponent(T* const component);
	template<typename T>
		requires (is_component_type<T>::value)
	void AddComponent();
	void AddComponent(ScriptComponent* const component);
	void AddComponent(Component* const component);

	void RemoveComponent(const eComponentType componentType);
	void RemoveComponent(const eScriptComponentType scriptComponentType);

	// 0 ~ 31
	eLayerType GetLayer() const { return mCurLayer;}; 
	GameObject* GetParentOrNull() const { return mParent; }
	eState GetState() const { return mState; }

	//FIXME:
	void SetParent(GameObject* const parent) { mParent = parent; }

	void RegisterSetStateEvent(const eState stateType);


private:
	void initialize();
	void update();
	void lateUpdate();	

private:
	eLayerType mCurLayer;
	eState mState;
	Component* mEngineComponents[static_cast<UINT>(eComponentType::End)];
	std::vector<ScriptComponent*> mUserComponents;
	GameObject* mParent;
};

template<typename T>
	requires (is_component_type<T>::value)
inline void GameObject::AddComponent(T* const component)
{	
	Assert(component, WCHAR_IS_NULLPTR);
	Assert(!(component->mOwner), WCHAR_IS_NOT_NULLPTR);

	if constexpr (engine_component_type<T>::value)
	{
		Assert(!mEngineComponents[static_cast<UINT>(engine_component_type<T>::type)], WCHAR_IS_NOT_NULLPTR);
		mEngineComponents[static_cast<UINT>(engine_component_type<T>::type)] = component;
	}
	else if constexpr (script_component_type<T>::value)
	{
		for (const ScriptComponent* const P_SCRIPT : mUserComponents)
		{			
			if (P_SCRIPT->GetScriptType() == script_component_type<T>::type)
			{
				Assert(false, WCHAR_IS_INVALID_TYPE);
				break;
			}
		}

		mUserComponents.push_back(component);
	}

	component->mOwner = this;
}

template<typename T>
	requires (is_component_type<T>::value)
inline void GameObject::AddComponent()
{
	T* const component = new T();
	Assert(component, WCHAR_IS_NULLPTR);

	AddComponent(component);
}

template<typename T>
	requires (is_component_type<T>::value)
inline T* GameObject::GetComponentOrNull() const
{
	T* component = nullptr;

	if constexpr (engine_component_type<T>::value) // engine component
	{
		component = dynamic_cast<T*>(mEngineComponents[static_cast<UINT>(engine_component_type<T>::type)]);
	}
	else if constexpr (script_component_type<T>::value) // user component
	{
		for (ScriptComponent* const script : mUserComponents)
		{
			if (script->GetScriptType() == script_component_type<T>::type)
			{
				component = dynamic_cast<T*>(script);
				break;
			}
		}
	}

	return component;
}

template<typename T>
	requires (is_component_type<T>::value)
inline T* GameObject::GetComponent() const
{	
	T* component = GetComponentOrNull<T>();
	Assert(component, WCHAR_IS_NULLPTR);

	return component;
}
