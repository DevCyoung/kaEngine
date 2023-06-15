#pragma once

#include "Entity.h"
#include "Component.h"
#include "Transform.h"
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
		//FIXME! 이벤트방식으로 변경해야함
		void AddComponent(Component* const component);

		template<typename T>
		T* GetComponent()
		{			
			const UINT index = static_cast<UINT>(enable_if_component<T>::type);
			T* component = dynamic_cast<T*>(mEngineComponents[index]);

			assert(component);
			return component;
		}

	private:
		void initialize();
		void update();
		void lateUpdate();
		void render();

	private:
		eState mState;
		Component* mEngineComponents[static_cast<int>(eComponentType::End)];		
	};
}
