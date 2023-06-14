#pragma once
#include "Entity.h"
#include "Shader.h"

namespace engine
{
	class GameObject : public Entity
	{
		friend class Layer;
	public:
		enum eState
		{
			Active,
			Paused,
			Dead,
		};
		GameObject();
		virtual ~GameObject();

	private:
		virtual void initialize();
		virtual void update();
		virtual void lateUpdate();
		virtual void render();

	private:
		eState mState;
		Shader mShader;
		//std::vector<Component*> mComponents;
		float mX;
		float mY;
		//int y;
		//int x;
	};
}