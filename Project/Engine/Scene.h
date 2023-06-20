#pragma once
#include "Entity.h"
#include "Layer.h"

namespace engine
{
	class GameObject;
	enum class eLayerType;

	class Scene : public Entity
	{
		friend class Engine;
		friend class SceneManager;

	public:
		Scene();
		virtual ~Scene();

		void AddGameObject(GameObject* const obj, eLayerType type);

	private:
		virtual void initialize();
		virtual void update();
		virtual void lateUpdate();
		virtual void render();


	private:
		Layer mLayers[static_cast<UINT>(eLayerType::End)];
	};
}
