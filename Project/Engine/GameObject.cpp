#include "pch.h"
#include "GameObject.h"

#include "GraphicDeviceDx11.h"
#include "CBCollection.h"

#include "InputManager.h"
#include "TimeManager.h"

namespace engine
{
	GameObject::GameObject()
		: mState(GameObject::Active)
		, mShader(L"VertexShader.hlsl", L"main", L"PixelShader.hlsl", L"main")
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
		gGraphicDevice->PassCB(gConstantBuffers->GetCBTransform(), &pos);
	}

	void GameObject::lateUpdate()
	{

	}

	void GameObject::render(/*mGraphicDevice*/)
	{			
		gGraphicDevice->BindIA(mShader);
		gGraphicDevice->BindPS(mShader);
		gGraphicDevice->BindVS(mShader);
		gGraphicDevice->BindCB(eShaderStage::VS, gConstantBuffers->GetCBTransform());
		gGraphicDevice->Draw();
	}
}