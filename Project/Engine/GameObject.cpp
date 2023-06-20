#include "pch.h"
#include "GameObject.h"

namespace engine
{
	GameObject::GameObject()
		: mState(eState::Active)
		, mEngineComponents{ 0, }
	{
		//모든 오브젝트는 반드시 Transform 을 가지고있는다.
		AddComponent(new Transform);
	}

	GameObject::~GameObject()
	{
		memory::safe::DeleteVec(mUserComponents);
		memory::unsafe::DeleteArray(mEngineComponents);
	}

	void GameObject::AddComponent(Component* const component)
	{
		assert(component);
		assert(!(component->mOwner));

		const eComponentType type = component->GetType();
		assert(eComponentType::End != type);

		if (eComponentType::Script == type)
		{
			Script* const addScript = dynamic_cast<Script*>(component);
			assert(addScript);

			for (const Script* const curScript : mUserComponents)
			{
				//이미존재한다면
				if (curScript->GetScriptType() == addScript->GetScriptType())
				{
					assert(false);
					break;
				}
			}

			mUserComponents.push_back(addScript);
		}
		else
		{
			assert(!mEngineComponents[static_cast<UINT>(type)]);
			mEngineComponents[static_cast<UINT>(type)] = component;
		}

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

		for (Script* const script : mUserComponents)
		{
			script->initialize();
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

		for (Script* const script : mUserComponents)
		{
			script->update();
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

		for (Script* const script : mUserComponents)
		{
			script->lateUpdate();
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


		for (Script* const script : mUserComponents)
		{
			script->render();
		}
	}
}