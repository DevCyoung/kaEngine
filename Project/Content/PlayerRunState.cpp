#include "pch.h"
#include "PlayerRunState.h"
#include "PlayerFSM.h"
#include "Components.h"
#include "Rect2DInterpolation.h"
#include <Engine/EngineMath.h>

#include <Engine/RenderTargetRenderer.h>
#include <Engine/DebugRenderer2D.h>
#include <Engine/Physics2D.h>

PlayerRunState::PlayerRunState(GameObject* const gameObject, PlayerFSM* const owner)
	: PlayerState(gameObject, owner)
{
}

PlayerRunState::~PlayerRunState()
{
}

void PlayerRunState::InputUpdate()
{
}

void PlayerRunState::Update()
{
	const Vector2 dir = mOwner->mPlayerGlobalState->GetInputDirectionX();

	Vector2 right = Vector2::Right;


	{
		RenderTargetRenderer* const renderer = mGameObject->GetGameSystem()->GetRenderTargetRenderer();
		DebugRenderer2D* const debugRenderer = renderer->GetDebugRenderer2D();
	
		Vector3 pos = mTransform->GetComponent<Transform>()->GetPosition();
	
		Matrix mat = mTransform->GetComponent<RectCollider2D>()->GetColliderWorldMatrix();
	
		Vector3 lp = Vector3(-0.5f, -0.5f, 0.f);
	
		lp = XMVector3TransformCoord(lp, mat);
	
		pos = lp;

		pos.y += 0.2f;

		//

		RayCast2DHitInfo info = {};
		Vector2 lp2 = Vector2(pos.x, pos.y);
		bool rs = mGameObject->GetGameSystem()->GetPhysics2D()->RayCastHit2D(lp2, Vector2::Down, 100.f, eLayerType::Slope, &info);

		if (rs)
		{
			debugRenderer->DrawLine2D2(pos, Vector2::Down, 100.f, 0.f, Vector4(1.f, 0.f, 0.f, 1.f));
		}
		else
		{
			debugRenderer->DrawLine2D2(pos, Vector2::Down, 100.f, 0.f, Vector4(1.f, 1.f, 1.f, 1.f));
		}
		


		if (rs)
		{
			right = Vector2(cos(Deg2Rad(-45)), sin(Deg2Rad(-45)));
		}

	}

	

	

	mOwner->mPlayerGlobalState->InputFlip();


	if (abs(mRigidbody->GetVelocity().x) < 400.f)
	{
		mRigidbody->AddForce(right * dir.x * 4000.f);
	}
	else if (gInput->GetKeyDown(eKeyCode::A) || gInput->GetKeyDown(eKeyCode::D))
	{
		mRigidbody->SetVelocity(right * dir.x * 400.f);
	}

	if (mOwner->mPlayerGlobalState->IsRollInput())
	{
		mOwner->ChangeState(mOwner->mPlayerRollState);
	}
	else if (!mOwner->mPlayerGlobalState->IsInputMoveKey() || dir.x == 0.f)
	{
		mOwner->mPlayerGlobalState->RunToIdle();
	}
}

void PlayerRunState::Enter()
{
	Animator2D* const animator = mGameObject->GetComponent<Animator2D>();

	animator->Play(L"IdleToRun", false);
}

void PlayerRunState::Exit()
{
}
