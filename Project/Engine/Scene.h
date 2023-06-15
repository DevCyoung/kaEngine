#pragma once
#include "Entity.h"
#include "Layer.h"

namespace engine
{
	class GameObject;

	class Scene : public Entity
	{
		friend class Engine;	
		friend class SceneManager;

	private:
		Scene();
		virtual ~Scene();

	private:
		virtual void initialize();
		virtual void update();
		virtual void lateUpdate();
		virtual void render();

	private:
		Layer mLayers[static_cast<UINT>(eLayerType::End)];
	};
}
