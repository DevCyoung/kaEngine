#pragma once
class GameObject;

class Layer
{
	friend class Scene;

private:
	Layer();
	virtual ~Layer();
	Layer(const Layer&) = delete;
	Layer& operator=(const Layer&) = delete;

	const std::vector<GameObject*>& GetGameObjects() const { return mGameObjects; }

	void AddGameObject(GameObject* const obj);

private:
	virtual void initialize();
	virtual void update();
	virtual void lateUpdate();

private:
	std::vector<GameObject*> mGameObjects;
};
