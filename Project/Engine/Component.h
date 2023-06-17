#pragma once
#include "Entity.h"
#include "EnumConponent.h"

namespace engine
{
	class GameObject;

	class Component : public Entity
	{		
		friend class GameObject;
	public:
		Component(const eComponentType type);
		virtual ~Component();
		Component(const Component&) = delete;
		Component& operator=(const Component&) = delete;

	public:
		GameObject* GetOwner() const { assert(mOwner); return mOwner; }
		eComponentType GetType() const { return mType; }

	private:
		virtual void initialize();
		virtual void update();
		virtual void lateUpdate();
		virtual void render();

	private:
		eComponentType mType;
		GameObject* mOwner;
	};
}
