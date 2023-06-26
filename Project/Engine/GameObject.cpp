#include "pch.h"
#include "GameObject.h"
#include "Transform.h"
#include "ScriptComponent.h"

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

Component* GameObject::GetComponentOrNull(eComponentType type) const
{
	return mEngineComponents[static_cast<UINT>(type)];
}

Component* GameObject::GetComponent(eComponentType type) const
{
	Component* const component = GetComponentOrNull(type);
	Assert(component, WCHAR_IS_NULLPTR);

	return component;
}

ScriptComponent* GameObject::GetComponentOrNull(eScriptComponentType type) const
{
	ScriptComponent* component = nullptr;

	for (ScriptComponent* const curScript : mUserComponents)
	{
		if (curScript->GetScriptType() == type)
		{
			component = curScript;
			break;
		}
	}
	return component;
}

ScriptComponent* GameObject::GetComponent(eScriptComponentType type) const
{
	ScriptComponent* component = GetComponentOrNull(type);
	Assert(component, WCHAR_IS_NULLPTR);

	return component;
}

void GameObject::RemoveComponent(eComponentType type)
{
	SAFE_DELETE_POINTER(mEngineComponents[static_cast<UINT>(type)]);
}

void GameObject::RemoveComponent(eScriptComponentType type)
{
	std::vector<ScriptComponent*>::iterator iter = mUserComponents.begin();

	for (; iter != mUserComponents.end(); ++iter)
	{
		if ((*iter)->GetScriptType() == type)
		{
			SAFE_DELETE_POINTER(*iter);
			mUserComponents.erase(iter);
			return;
		}
	}

	Assert(false, WCHAR_IS_INVALID_TYPE);
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

	for (ScriptComponent* const script : mUserComponents)
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

	for (ScriptComponent* const script : mUserComponents)
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

	for (ScriptComponent* const script : mUserComponents)
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


	for (ScriptComponent* const script : mUserComponents)
	{
		script->render();
	}
}
