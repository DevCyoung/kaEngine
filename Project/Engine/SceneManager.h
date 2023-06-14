#pragma once

#include "Scene.h"
#include "Singleton.h"



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