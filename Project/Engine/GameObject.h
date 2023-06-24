#pragma once
#include "Entity.h"
#include "Transform.h"
#include "Script.h"
#include "EenableIfComponent.h"

namespace engine
{
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
		//bool HasComponent(const eComponentType type) const;

		//FIXME! 이벤트방식으로 변경해야함
		void AddComponent(Component* const component);

		template<typename T>
			requires std::is_base_of_v<Component, T>
		void AddComponent()
		{
			T* component = new T();
			Assert(component, WCHAR_IS_NULLPTR);

			AddComponent(component);
		}

		template<typename T>
			requires std::is_base_of_v<Component, T>
		T* GetComponentOrNull() const
		{
			constexpr eComponentType type = enable_if_component<T>::type;
			Assert(eComponentType::End != type, WCHAR_IS_INVALID_TYPE);

			T* component = nullptr;
			if constexpr (eComponentType::Script == type) // user script
			{
				for (Script* const script : mUserComponents)
				{
					if (script->GetScriptType() == enable_if_script<T>::type)
					{
						component = dynamic_cast<T*>(script);
						break;
					}					
				}
			}
			else // engine component
			{
				component = dynamic_cast<T*>(mEngineComponents[static_cast<UINT>(type)]);
			}

			return component;
		}

		template<typename T>
			requires std::is_base_of_v<Component, T>
		T* GetComponent() const
		{
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
		std::vector<Script*> mUserComponents;
	};
}
