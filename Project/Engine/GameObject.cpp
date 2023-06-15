#include "pch.h"
#include "GameObject.h"

#include "GraphicDeviceDx11.h"
#include "ShaderCollection.h"
#include "CBCollection.h"

#include "Engine.h"
#include "InputManager.h"
#include "TimeManager.h"

namespace engine
{
	GameObject::GameObject()
		: mState(GameObject::Active)		
		, mX(0.f)
		, mY(0.f)
	{		
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::initialize()
	{
	}

	void GameObject::update()
	{
		
		const float speed = 0.5f;
		if (gInput->GetKey(eKeyCode::W))
		{
			mY += speed * gDeltaTime;
		}
		if (gInput->GetKey(eKeyCode::S))
		{
			mY -= speed * gDeltaTime;
		}
		if (gInput->GetKey(eKeyCode::A))
		{
			mX -= speed * gDeltaTime;
		}
		if (gInput->GetKey(eKeyCode::D))
		{
			mX += speed * gDeltaTime;
		}

		const Vector4 pos = { mX, mY, 0.f, 0.f };

		gGraphicDevice->PassCB(eCBType::Transform, &pos);

	}

	void GameObject::lateUpdate()
	{
	}

	void GameObject::render(/*mGraphicDevice*/)
	{		
		gGraphicDevice->BindIA(eShaderType::Default);
		gGraphicDevice->BindPS(eShaderType::Default);
		gGraphicDevice->BindVS(eShaderType::Default);
		gGraphicDevice->BindCB(eCBType::Transform, eShaderStage::VS);
		gGraphicDevice->Draw();
	}
}