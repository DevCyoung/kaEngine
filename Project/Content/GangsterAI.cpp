#include "pch.h"
#include "GangsterAI.h"
#include "Components.h"
#include "Rect2DInterpolation.h"

GangsterAI::GangsterAI()
	: ScriptComponent(eScriptComponentType::GangsterAI)
	, prevPlayerPathNode(nullptr)
{
}

GangsterAI::~GangsterAI()
{
}

void GangsterAI::initialize()
{
}

void GangsterAI::update()
{
	GameObject* const player = GameManager::GetInstance()->GetPlayer();

	Transform* const playerTransform = player->GetComponent<Transform>();
	Transform* const transform = GetOwner()->GetComponent<Transform>();

	Vector3 playerPos = playerTransform->GetPosition();


	PathNode* myNode = GetOwner()->GetComponent<PlayerPath>()->GetCurPathNode();

	if (nullptr == prevPlayerPathNode)
	{
		prevPlayerPathNode = player->GetComponent<PlayerPath>()->GetCurPathNode();
	}
	else if (prevPlayerPathNode != player->GetComponent<PlayerPath>()->GetCurPathNode()) // player node changed
	{
		prevPlayerPathNode = player->GetComponent<PlayerPath>()->GetCurPathNode();
		PathInfo* const pathInfo = GameManager::GetInstance()->GetPathInfo();
		mPath = pathInfo->Dijikstra(myNode->GetIdx(), prevPlayerPathNode->GetIdx());
	}

	if (nullptr == myNode)
	{
		return;
	}

	Assert(myNode, WCHAR_IS_NULLPTR);

	Rigidbody2D* const rigidbody2D = GetOwner()->GetComponent<Rigidbody2D>();
	Vector2 direction = Vector2::Zero;

	rigidbody2D->SetVelocity(Vector2::Zero);

	if (mPath.empty())
	{

		if (playerPos.x < transform->GetPosition().x)
		{
			direction.x = -1.f;
		}
		else if (playerPos.x > transform->GetPosition().x)
		{
			direction.x = 1.f;
		}

		if (direction.x < 0.f)
		{
			transform->SetRotation(0.f, 180.f, 0.f);
		}
		else
		{
			transform->SetRotation(0.f, 0.f, 0.f);
		}



		rigidbody2D->SetVelocity(direction * 200.f);

		return;
	}




	PathNode* nextNode = mPath.front();

	if (nextNode == myNode)
	{
		if (playerPos.x < transform->GetPosition().x)
		{
			direction.x = -1.f;
		}
		else if (playerPos.x > transform->GetPosition().x)
		{
			direction.x = 1.f;
		}

		rigidbody2D->SetVelocity(direction * 200.f);

		mPath.pop();
	}



	Vector2 nodePos = nextNode->GetPosition();

	Rect2DInterpolation* const rect2DInterpolation = GetOwner()->GetComponent<Rect2DInterpolation>();


	if (nodePos.x < transform->GetPosition().x)
	{
		direction.x = -1.f;
	}
	else if (nodePos.x > transform->GetPosition().x)
	{
		direction.x = 1.f;
	}

	switch (nextNode->GetType())
	{
	case eLayerType::Wall: //just move direction...
	{
		rect2DInterpolation->TurnOnPlatform();
	}
	break;

	case eLayerType::Elevator: //elevator
	{
		rect2DInterpolation->TurnOnPlatform();

		Vector3 elevatorPos = Vector3(nextNode->GetPosition().x, nextNode->GetPosition().y, 0.);
		elevatorPos.z = 0.f;
		Vector3 myPos = transform->GetPosition();
		myPos.z = 0.f;

		if (Vector3::Distance(elevatorPos, myPos) < 30.f)
		{
			mPath.pop();
			nextNode = mPath.front();

			if (nextNode->GetType() == eLayerType::Elevator)
			{
				nodePos = nextNode->GetPosition();
				transform->SetPosition(Vector3(nodePos.x, nodePos.y - 25.f, transform->GetPosition().z));
				mPath.pop();
			}

		}
	}
	break;

	case eLayerType::LeftSlope: // up down ?
	{
		if (nodePos.y < transform->GetPosition().y) //down
		{
			rect2DInterpolation->TurnOffPlatform();
		}
		else // up
		{
			rect2DInterpolation->TurnOnPlatform();
		}
	}
	break;

	case eLayerType::RightSlope: // up down ?
	{
		if (nodePos.y < transform->GetPosition().y) //down
		{
			rect2DInterpolation->TurnOffPlatform();
		}
		else // up
		{
			rect2DInterpolation->TurnOnPlatform();
		}
	}
	break;

	default:
	{

	}
	break;
	}


	if (direction.x < 0.f)
	{
		transform->SetRotation(0.f, 180.f, 0.f);
	}
	else
	{
		transform->SetRotation(0.f, 0.f, 0.f);
	}

	rigidbody2D->SetVelocity(direction * 200.f);
}

void GangsterAI::lateUpdate()
{
}
