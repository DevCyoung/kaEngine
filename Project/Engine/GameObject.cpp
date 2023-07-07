﻿#include "pch.h"
#include "GameObject.h"
#include "Transform.h"
#include "ScriptComponent.h"
#include "EnumLayer.h"

GameObject::GameObject()
	: mCurLayer(eLayerType::Default)
	, mState(eState::Active)
	, mEngineComponents{0, }
	, mUserComponents()
	, mParent(nullptr)
{
	//모든 오브젝트는 반드시 Transform 을 가지고있는다.
	AddComponent<Transform>();

}

GameObject::~GameObject()
{
	memory::safe::DeleteVec(mUserComponents);
	memory::unsafe::DeleteArray(mEngineComponents);
}

void GameObject::AddComponent(ScriptComponent* const component)
{
	Assert(component, WCHAR_IS_NULLPTR);
	Assert(!(component->mOwner), WCHAR_IS_NOT_NULLPTR);

	for (const ScriptComponent* const curScript : mUserComponents)
	{
		if (curScript->GetScriptType() == component->GetScriptType())
		{
			Assert(false, "already Exist Script");
			break;
		}
	}

	mUserComponents.push_back(component);
	component->mOwner = this;
}

void GameObject::AddComponent(Component* const component)
{
	Assert(component, WCHAR_IS_NULLPTR);
	Assert(!(component->mOwner), WCHAR_IS_NOT_NULLPTR);

	if (component->GetType() != eComponentType::ScriptComponent)
	{
		Assert(!mEngineComponents[static_cast<UINT>(component->GetType())], WCHAR_IS_NOT_NULLPTR);
		mEngineComponents[static_cast<UINT>(component->GetType())] = component;
	}
	else
	{
		ScriptComponent* const scriptComponent = dynamic_cast<ScriptComponent*>(component);
		AddComponent(scriptComponent);
	}

	component->mOwner = this;
}

Component* GameObject::GetComponentOrNull(const eComponentType COMPONENT_TYPE) const
{
	return mEngineComponents[static_cast<UINT>(COMPONENT_TYPE)];
}

ScriptComponent* GameObject::GetComponentOrNull(const eScriptComponentType SCRIPT_COMPONENT_TYPE) const
{
	ScriptComponent* component = nullptr;

	for (ScriptComponent* const curScript : mUserComponents)
	{
		if (curScript->GetScriptType() == SCRIPT_COMPONENT_TYPE)
		{
			component = curScript;
			break;
		}
	}
	return component;
}

void GameObject::RemoveComponent(eComponentType COMPONENT_TYPE)
{
	Assert(false, WCHAR_IS_INVALID_TYPE);

	SAFE_DELETE_POINTER(mEngineComponents[static_cast<UINT>(COMPONENT_TYPE)]);
}

void GameObject::RemoveComponent(eScriptComponentType SCRIPT_COMPONENT_TYPE)
{
	Assert(false, WCHAR_IS_INVALID_TYPE);

	std::vector<ScriptComponent*>::iterator iter = mUserComponents.begin();

	for (; iter != mUserComponents.end(); ++iter)
	{
		if ((*iter)->GetScriptType() == SCRIPT_COMPONENT_TYPE)
		{
			SAFE_DELETE_POINTER(*iter);
			mUserComponents.erase(iter);
			return;
		}
	}

	Assert(false, WCHAR_IS_INVALID_TYPE);
}

void GameObject::RegisterSetStateEvent(const eState STATE_TYPE)
{
	//Event Manager -> Set State
	(void)STATE_TYPE;
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
