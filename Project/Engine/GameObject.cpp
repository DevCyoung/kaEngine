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
		Assert(component, WCHAR_IS_NULLPTR);
		Assert(!(component->mOwner), WCHAR_IS_NOT_NULLPTR);

		const eComponentType type = component->GetType();
		Assert(eComponentType::End != type, WCHAR_IS_INVALID_TYPE);

		if (eComponentType::Script == type)
		{
			Script* const addScript = dynamic_cast<Script*>(component);
			Assert(addScript, WCHAR_IS_NULLPTR);			

			for (const Script* const curScript : mUserComponents)
			{
				//이미존재한다면
				if (curScript->GetScriptType() == addScript->GetScriptType())
				{					
					Assert(false, "already Exist Script");
					break;
				}
			}

			mUserComponents.push_back(addScript);
		}
		else
		{
			Assert(!mEngineComponents[static_cast<UINT>(type)], WCHAR_IS_NOT_NULLPTR);
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