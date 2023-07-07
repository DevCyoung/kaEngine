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

private:
	virtual void initialize();
	virtual void update();
	virtual void lateUpdate();

private:
	std::vector<GameObject*> mGameObjects;
};
