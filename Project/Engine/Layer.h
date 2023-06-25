#pragma once


class GameObject;

enum class eLayerType
{
	Player,
	End
};

class Layer
{
	friend class Scene;

private:
	Layer();
	virtual ~Layer();
	Layer(const Layer&) = delete;
	Layer& operator=(const Layer&) = delete;

	void AddGameObject(GameObject* const obj);

private:
	virtual void initialize();
	virtual void update();
	virtual void lateUpdate();
	virtual void render();

private:
	std::vector<GameObject*> mGameObjects;
};
