#include "Singleton.h"
#include "Scene.h"

class GameObject;

class SceneManager
{
	friend class Engine;
	SINGLETON_DECLARE(SceneManager);

public:
	void LoadScene(Scene* const scene);

private:
	void update();
	void lateUpdate();

private:
	Scene* mCurrentScene;
};
