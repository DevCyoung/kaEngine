#pragma once
#include "Entity.h"
#include "Component.h"
#include "Transform.h"
#include "ScriptComponent.h"

class GameObject : public Entity
{
	friend class Layer;
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
		requires std::is_base_of_v<Component, T>
	void AddComponent(T* const component)
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
				//이미존재한다면
				if (curScript->GetScriptType() == script_component_type<T>::type)
				{
					Assert(false, "already Exist Script");
					break;
				}
			}
			mUserComponents.push_back(component);
		}

		component->mOwner = this;
	}

	//특수화
	template<>
	void AddComponent(ScriptComponent* const component)
	{
		Assert(component, WCHAR_IS_NULLPTR);
		Assert(!(component->mOwner), WCHAR_IS_NOT_NULLPTR);

		for (const ScriptComponent* const curScript : mUserComponents)
		{
			if (curScript->GetScriptType() == component->GetScriptType())
			{
				//이미존재한다면
				Assert(false, "already Exist Script");
				break;
			}
		}

		mUserComponents.push_back(component);

		component->mOwner = this;
	}

	//특수화
	template<>
	void AddComponent(Component* const component)
	{
		Assert(component, WCHAR_IS_NULLPTR);
		Assert(!(component->mOwner), WCHAR_IS_NOT_NULLPTR);

		if (component->GetType() != eComponentType::ScriptComponent)
		{
			Assert(!mEngineComponents[static_cast<UINT>(component->GetType())], WCHAR_IS_NOT_NULLPTR);
			mEngineComponents[static_cast<UINT>(component->GetType())] = component;
		}
		else
		{
			ScriptComponent* const scriptComponent = dynamic_cast<ScriptComponent*>(component);
			AddComponent(scriptComponent);
		}

		component->mOwner = this;
	}

	template<typename T>
		requires std::is_base_of_v<Component, T>
	void AddComponent()
	{
		static_assert(engine_component_type<T>::value || script_component_type<T>::value);

		T* const component = new T();
		Assert(component, WCHAR_IS_NULLPTR);

		AddComponent(component);
	}

	template<typename T>
		requires std::is_base_of_v<Component, T>
	T* GetComponentOrNull() const
	{
		static_assert(engine_component_type<T>::value || script_component_type<T>::value);

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
		requires std::is_base_of_v<Component, T>
	T* GetComponent() const
	{
		static_assert(engine_component_type<T>::value || script_component_type<T>::value);

		T* component = GetComponentOrNull<T>();

		Assert(component, WCHAR_IS_NULLPTR);
		return component;
	}

private:
	void initialize();
	void update();
	void lateUpdate();
	void render();

private:
	eState mState;
	Component* mEngineComponents[static_cast<UINT>(eComponentType::End)];
	std::vector<ScriptComponent*> mUserComponents;
};
