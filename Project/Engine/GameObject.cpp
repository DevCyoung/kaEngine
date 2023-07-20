#include "pch.h"
#include "GameObject.h"
#include "Transform.h"
#include "ScriptComponent.h"
#include "EnumLayer.h"

GameObject::GameObject()
	: mEngineComponents{0, }
	, mUserComponents()
	, mLayerType(eLayerType::Default)
	, mState(eState::Active)
	, mParent(nullptr)
	, mGameSystem(nullptr)
{
	AddComponent<Transform>();
}

GameObject::~GameObject()
{
	memory::safe::DeleteVec(mUserComponents);
	memory::unsafe::DeleteArray(mEngineComponents);
}

void GameObject::initialize()
{
	Assert(mGameSystem, WCHAR_IS_NULLPTR);

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

void GameObject::AddComponent(ScriptComponent* const scriptComponent)
{
	Assert(scriptComponent, WCHAR_IS_NULLPTR);
	Assert(!(scriptComponent->mOwner), WCHAR_IS_NOT_NULLPTR);
	Assert(!(GetComponentOrNull(scriptComponent->GetScriptType())), WCHAR_IS_NOT_NULLPTR);

	scriptComponent->mOwner = this;

	mUserComponents.push_back(scriptComponent);
}

void GameObject::AddComponent(Component* const component)
{
	Assert(component, WCHAR_IS_NULLPTR);
	Assert(!(component->mOwner), WCHAR_IS_NOT_NULLPTR);

	component->mOwner = this;

	if (component->GetType() == eComponentType::ScriptComponent)
	{
		ScriptComponent* const scriptComponent = dynamic_cast<ScriptComponent*>(component);

		Assert(scriptComponent, WCHAR_IS_NULLPTR);

		AddComponent(scriptComponent);
	}
	else
	{
		Assert(!mEngineComponents[static_cast<UINT>(component->GetType())], WCHAR_IS_NOT_NULLPTR);

		mEngineComponents[static_cast<UINT>(component->GetType())] = component;
	}
}

Component* GameObject::GetComponentOrNull(const eComponentType componentType) const
{
	return mEngineComponents[static_cast<UINT>(componentType)];
}

ScriptComponent* GameObject::GetComponentOrNull(const eScriptComponentType scriptComponentType) const
{
	ScriptComponent* component = nullptr;

	for (ScriptComponent* const curScript : mUserComponents)
	{
		if (curScript->GetScriptType() == scriptComponentType)
		{
			component = curScript;

			break;
		}
	}

	return component;

}
void GameObject::RemoveComponent(eComponentType componentType)
{
	Assert(false, WCHAR_IS_INVALID_TYPE);

	SAFE_DELETE_POINTER(mEngineComponents[static_cast<UINT>(componentType)]);
}

void GameObject::RemoveComponent(eScriptComponentType scriptComponentType)
{
	Assert(false, WCHAR_IS_INVALID_TYPE);

	std::vector<ScriptComponent*>::iterator iter = mUserComponents.begin();

	for (; iter != mUserComponents.end(); ++iter)
	{
		if ((*iter)->GetScriptType() == scriptComponentType)
		{
			SAFE_DELETE_POINTER(*iter);
			mUserComponents.erase(iter);

			return;
		}
	}

	Assert(false, WCHAR_IS_INVALID_TYPE);
}
