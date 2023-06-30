#pragma once
#include "Entity.h"
#include "ComponentTrait.h"
#include "EnumComponent.h"

class ScriptComponent;

class GameObject : public Entity
{
	friend class Layer;
	friend class RenderManager;
public:
	enum class eState
	{
		Active,
		Paused,
		Dead,
	};

	GameObject();
	virtual ~GameObject();
	GameObject(const GameObject&) = delete;
	GameObject& operator=(const GameObject&) = delete;

public:
	//FIXME! 이벤트방식으로 변경해야함
	template<typename T>
		requires (is_component_type<T>::value)
	void AddComponent(T* const component);
	template<typename T>
		requires (is_component_type<T>::value)
	void AddComponent();
	void AddComponent(ScriptComponent* const component);
	void AddComponent(Component* const component);

	template<typename T>
		requires (is_component_type<T>::value)
	T* GetComponentOrNull() const;

	template<typename T>
		requires (is_component_type<T>::value)
	T* GetComponent() const;
	Component* GetComponentOrNull(const eComponentType type) const;
	ScriptComponent* GetComponentOrNull(const eScriptComponentType type) const;

	void RemoveComponent(eComponentType type);
	void RemoveComponent(eScriptComponentType type);

	UINT GetLayer() const { return mCurLayer;}; // 0 ~ 31

private:
	void initialize();
	void update();
	void lateUpdate();
	void render();

private:
	UINT mCurLayer;
	eState mState;
	Component* mEngineComponents[static_cast<UINT>(eComponentType::End)];
	std::vector<ScriptComponent*> mUserComponents;
};

template<typename T>
	requires (is_component_type<T>::value)
inline void GameObject::AddComponent(T* const component)
{
	static_assert(engine_component_type<T>::value || script_component_type<T>::value);
	Assert(component, WCHAR_IS_NULLPTR);
	Assert(!(component->mOwner), WCHAR_IS_NOT_NULLPTR);

	if constexpr (engine_component_type<T>::value)
	{
		Assert(!mEngineComponents[static_cast<UINT>(engine_component_type<T>::type)], WCHAR_IS_NOT_NULLPTR);
		mEngineComponents[static_cast<UINT>(engine_component_type<T>::type)] = component;
	}
	else if constexpr (script_component_type<T>::value)
	{
		for (const ScriptComponent* const curScript : mUserComponents)
		{			
			if (curScript->GetScriptType() == script_component_type<T>::type)
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
