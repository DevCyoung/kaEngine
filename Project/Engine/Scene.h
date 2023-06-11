#pragma once
#include "Entity.h"

namespace engine
{
	class GameObject;

	class Scene : public Entity
	{
		friend class Engine;	
		Scene();
		virtual ~Scene();

	private:
		virtual void initialize();
		virtual void update();
		virtual void lateUpdate();
		virtual void render();

	private:
		std::vector<GameObject*> mGameObjects;
	};
}