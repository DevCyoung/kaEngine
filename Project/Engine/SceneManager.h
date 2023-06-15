#pragma once
#include "Singleton.h"

class Scene;

namespace engine
{		
	class SceneManager
	{
		friend class Engine;
		SINGLETON_DECLARE(SceneManager);

	private:
		void update();
		void lateUpdate();
		void render();

	private:
		Scene* mCurrentScene;
	};
}
