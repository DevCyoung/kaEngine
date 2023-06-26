#include "Singleton.h"
#include "Scene.h"

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
