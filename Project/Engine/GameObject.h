#pragma once
#include "Entity.h"

namespace engine
{
	class GameObject : public Entity
	{
		friend class Scene;
	public:
		enum eState
		{
			Active,
			Paused,
			Dead,
		};
		GameObject();
		virtual ~GameObject();

	private:
		virtual void initialize();
		virtual void update();
		virtual void lateUpdate();
		virtual void render();

	private:
		eState mState;
		//std::vector<Component*> mComponents;
		//int y;
		//int x;
	};
}