#include "Singleton.h"
#include "Scene.h"

class SceneManager
{
	friend class Engine;
	SINGLETON_DECLARE(SceneManager);

public:
	void LoadScene(Scene* const scene);

	//Scene* GetCurrentScene() { Assert(false, WCHAR_IS_NULLPTR); return mCurrentScene; }

private:
	void update();
	void lateUpdate();

private:
	Scene* mCurrentScene;
};
