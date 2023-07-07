#include "Singleton.h"
#include "Scene.h"

class GameObject;

class SceneManager
{
	friend class Engine;
	SINGLETON_DECLARE(SceneManager);

public:
	void LoadScene(Scene* const scene);
	Scene* GetCurrentScene() const { Assert(mCurrentScene, WCHAR_IS_NULLPTR); return mCurrentScene; }

private:
	void update();
	void lateUpdate();
	void eventUpdate();

private:
	Scene* mCurrentScene;	
};

#define gCurrentScene SceneManager::GetInstance()->GetCurrentScene()
