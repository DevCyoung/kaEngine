#include "pch.h"
#include "KatanaScene.h"

KatanaScene::KatanaScene()
{
}

KatanaScene::~KatanaScene()
{
	GameManager::deleteInstance();
}

void KatanaScene::SetDefaultCollision()
{
	mCollisionManagement2D->TurnOffAllCollisionLayer();
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Player, eLayerType::Wall);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Player, eLayerType::MonsterAttack);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Player, eLayerType::Platform);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Monster, eLayerType::LeftSlope);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Monster, eLayerType::RightSlope);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Monster, eLayerType::Wall);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Monster, eLayerType::Monster);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Monster, eLayerType::Platform);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Monster, eLayerType::Door);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Monster, eLayerType::PlayerAttack);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Player, eLayerType::Door);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Door, eLayerType::PlayerAttack);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Bullet, eLayerType::Monster);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Bullet, eLayerType::Player);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Bullet, eLayerType::PlayerAttack);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Bullet, eLayerType::Wall);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Bullet, eLayerType::Door);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Bullet, eLayerType::LeftSlope);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Bullet, eLayerType::RightSlope);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Camera, eLayerType::CameraWall);
	mCollisionManagement2D->TurnOnCollisionLayer(eLayerType::Wall, eLayerType::PlayerAttack);
}

void KatanaScene::initialize()
{
	SetDefaultCollision();

#pragma region Wave Reset
	tWaveInfo waveInfo = {};

	waveInfo.WaveXPower = 0.f;
	waveInfo.WaveYPower = 0.f;
	waveInfo.WaveSpeed = 0.f;

	gGraphicDevice->PassCB(eCBType::Wave, sizeof(waveInfo), &waveInfo);
	gGraphicDevice->BindCB(eCBType::Wave, eShaderBindType::PS);
#pragma endregion
#pragma region Editor
	//{
	//	GameObject* const testObj = new GameObject();
	//	testObj->AddComponent<SimpleEditorCollider2D>();
	//	AddGameObject(testObj, eLayerType::Default);
	//}
#pragma endregion
	AddMapObject();
	AddWallObject();
	AddDoorObject();
	AddObject();
	AddMonsterObject();
	AddCameraObject();
	AddLightObject();
	AddUIObject();

#pragma region NextScene Effect
	{
		GameObject* const effect = new GameObject();
		effect->AddComponent<SpriteRenderer>();
		effect->AddComponent<NexeScene>();

		effect->GetComponent<SpriteRenderer>()->SetMaterial(
			gResourceManager->FindOrNull<Material>(L"NextScene"));
		effect->GetComponent<SpriteRenderer>()->TurnOnVisiblelity();

		AddGameObject(effect, eLayerType::Default);
	}
#pragma endregion



#pragma region PostProcess
	{
		GameObject* const postProcess = new GameObject();
		postProcess->AddComponent<SpriteRenderer>();
		postProcess->GetComponent<SpriteRenderer>()->SetMaterial(
			gResourceManager->FindOrNull<Material>(L"GrayPostProcess"));
		postProcess->GetComponent<SpriteRenderer>()->TurnOffVisiblelity();
		AddGameObject(postProcess, eLayerType::Default);
	}

	{
		GameObject* const postProcess = new GameObject();
		postProcess->AddComponent<SpriteRenderer>();
		postProcess->GetComponent<SpriteRenderer>()->SetMaterial(
			gResourceManager->FindOrNull<Material>(L"WavePostProcess"));
		AddGameObject(postProcess, eLayerType::Default);
	}
#pragma endregion	

#pragma region GameManager Init
	GameManager::initialize();
	GameManager::GetInstance()->GetRewindManager()->SetRewindState(eRewindState::Record);
	GameManager::GetInstance()->GetRewindManager()->Initialize(this);
	GameManager::GetInstance()->GetEffectManager()->Initialize(this);
#pragma endregion

	AddPlayerObject();

	Scene::initialize();
	TimeManager::GetInstance()->ResetTime();
}

void KatanaScene::update()
{
	Scene::update();
}

void KatanaScene::lateUpdate()
{
	Scene::lateUpdate();

	GameManager::GetInstance()->GetRewindManager()->LateUpdate();
	GameManager::GetInstance()->GetEventManager()->LateUpdate();
}

GameObject* KatanaScene::InstantiateMonster(eMonsterType type, Vector2 pos, bool bFlipX)
{
	GameObject* monster = GameObjectBuilder::InstantiateMonster(type, this);
	monster->GetComponent<Transform>()->SetPosition(pos.x, pos.y, 0);
	monster->GetComponent<Transform>()->SetFlipx(bFlipX);
	return monster;
}
