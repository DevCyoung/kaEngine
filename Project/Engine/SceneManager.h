#pragma once
#include "Singleton.h"

class Scene;

namespace engine
{		
	class SceneManager
	{		
		friend class Engine;
		SINGLETON_DECLARE(SceneManager);

	public:
		void LoadScene(Scene* const scene);

	private:
		void update();
		void lateUpdate();
		void render();

	private:
		Scene* mCurrentScene;
	};
}