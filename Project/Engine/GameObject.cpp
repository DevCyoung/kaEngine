#include "pch.h"

#include "GameObject.h"
#include "MeshRenderer.h"

#include "Resources.h"
#include "Textrue.h"

#include "ResourceManager.h"
#include "EnumResourceType.h"

#include "Shader.h"

namespace engine
{
	GameObject::GameObject()
		: mState(eState::Active)
		, mEngineComponents{0, }		
	{		
		//모든 오브젝트는 반드시 Transform 을 가지고있는다.
		AddComponent(new Transform());		
		AddComponent(new MeshRenderer());
	}




	GameObject::~GameObject()
	{
		safe::DeleteArray(mEngineComponents);
	}

	void GameObject::AddComponent(Component* const component)
	{
		assert(component);
		assert(!(component->mOwner));

		const eComponentType type =  component->GetType();

		assert(!mEngineComponents[static_cast<UINT>(type)]);
		
		mEngineComponents[static_cast<int>(type)] = component;

		component->mOwner = this;
	}

	void GameObject::initialize()
	{
		for (Component* const component : mEngineComponents)
		{
			if (component)
			{
				component->initialize();
			}
		}
	}

	void GameObject::update()
	{
		for (Component* const component : mEngineComponents)
		{
			if (component)
			{
				component->update();
			}
		}
	}

	void GameObject::lateUpdate()
	{
		for (Component* const component : mEngineComponents)
		{
			if (component)
			{
				component->lateUpdate();
			}
		}
	}

	void GameObject::render(/*mGraphicDevice*/)
	{		
		for (Component* const component : mEngineComponents)
		{
			if (component)
			{
				component->render();
			}
		}
	}
}

