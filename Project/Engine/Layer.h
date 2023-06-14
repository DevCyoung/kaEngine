#pragma once

#include "GameObject.h"

namespace engine
{
	class Layer
	{
		friend class Scene;
	public:
		Layer();
		virtual ~Layer();
		Layer(const Layer&) = delete;
		Layer& operator=(const Layer&) = delete;

	private:
		virtual void initialize();
		virtual void update();
		virtual void lateUpdate();
		virtual void render();
		
	private:
		std::vector<GameObject*> mGameObjects;
	};
}
