#include "pch.h"
#include "KatanaScene.h"
#include "KatanaZeroSystem.h"
#include "NexeScene.h"
#include "CCTVTextDrawer.h"
#include "DieController.h"
KatanaScene::KatanaScene(const eKatanaSceneType type)
	: mKatanaSceneType(type)
	, mEnemyCount(0)
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

void KatanaScene::enter()
{

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




#pragma region PostProcess
	{
		GameObject* const postProcess = new GameObject();
		postProcess->AddComponent<SpriteRenderer>();
		postProcess->GetComponent<SpriteRenderer>()->SetMaterial(
			gResourceManager->FindOrNull<Material>(L"GrayPostProcess"));
		postProcess->GetComponent<SpriteRenderer>()->TurnOffVisiblelity();
		AddGameObject(postProcess, eLayerType::Default);

		gKatanaZeroSystem->SetCRTEffect(postProcess);
	}

	{
		GameObject* const postProcess = new GameObject();
		postProcess->AddComponent<SpriteRenderer>();
		postProcess->GetComponent<SpriteRenderer>()->SetMaterial(
			gResourceManager->FindOrNull<Material>(L"WavePostProcess"));
		AddGameObject(postProcess, eLayerType::Default);
	}

	{
		GameObject* const postProcess = new GameObject();
		postProcess->AddComponent<EngineText>();		

		//postProcess->GetComponent<EngineText>()->SetText(L"빨리감기");
		postProcess->GetComponent<EngineText>()->TurnOffCamera();

		postProcess->GetComponent<EngineText>()->SetMaterial(
			gResourceManager->FindOrNull<Material>(L"Text"));
		AddGameObject(postProcess, eLayerType::Default);

		gKatanaZeroSystem->SetCRTText(postProcess);
	}

	//Time
	{
		GameObject* const postProcess = new GameObject();
		postProcess->AddComponent<EngineText>();

		//postProcess->GetComponent<EngineText>()->SetText(L"빨리감기");
		postProcess->GetComponent<EngineText>()->TurnOffCamera();

		postProcess->GetComponent<EngineText>()->SetMaterial(
			gResourceManager->FindOrNull<Material>(L"Text"));
		AddGameObject(postProcess, eLayerType::Default);

		gKatanaZeroSystem->SetCRTTextTime(postProcess);
	}

	//Time line
	{
		GameObject* const postProcess = new GameObject();
		postProcess->AddComponent<EngineText>();

		//postProcess->GetComponent<EngineText>()->SetText(L"빨리감기");
		postProcess->GetComponent<EngineText>()->TurnOffCamera();

		postProcess->GetComponent<EngineText>()->SetMaterial(
			gResourceManager->FindOrNull<Material>(L"Text"));
		AddGameObject(postProcess, eLayerType::Default);

		gKatanaZeroSystem->SetCRTTimeLine(postProcess);
	}

	//Time line bar
	{
		GameObject* const postProcess = new GameObject();
		postProcess->AddComponent<EngineText>();

		//postProcess->GetComponent<EngineText>()->SetText(L"빨리감기");
		postProcess->GetComponent<EngineText>()->TurnOffCamera();

		postProcess->GetComponent<EngineText>()->SetMaterial(
			gResourceManager->FindOrNull<Material>(L"Text"));
		AddGameObject(postProcess, eLayerType::Default);

		gKatanaZeroSystem->SetCRTTimeLineBar(postProcess);
	}

	//BlackOut
	{
		GameObject* const postProcess = new GameObject();
		postProcess->AddComponent<SpriteRenderer>();

		postProcess->GetComponent<Transform>()->SetScale(10000.f, 10000.f, 1.f);
		postProcess->GetComponent<SpriteRenderer>()->SetColorA(0.0f);

		postProcess->GetComponent<SpriteRenderer>()->SetMaterial(
			gResourceManager->FindOrNull<Material>(L"BlackOut"));
		postProcess->GetComponent<SpriteRenderer>()->TurnOffVisiblelity();

		AddGameObject(postProcess, eLayerType::UI);

		gKatanaZeroSystem->SetCRTBlackOut(postProcess);
	}

	//그래, 이렇게 하면 되겠지.
	{
		GameObject* const postProcess = new GameObject();

		postProcess->AddComponent<EngineText>();
		postProcess->GetComponent<EngineText>()->SetPosition(XMUINT2(520, 320));
		postProcess->GetComponent<EngineText>()->SetText(L"그래, 이렇게 하면 되겠지.");
		postProcess->GetComponent<EngineText>()->SetColor(XMUINT4(255, 255, 255, 0));
		//postProcess->GetComponent<EngineText>()->TurnOffVisiblelity();
		
		postProcess->GetComponent<EngineText>()->TurnOffCamera();

		postProcess->GetComponent<EngineText>()->SetMaterial(
			gResourceManager->FindOrNull<Material>(L"Text"));
		AddGameObject(postProcess, eLayerType::Default);

		gKatanaZeroSystem->SetCRTReadyText(postProcess);
	}


	//BlackOut
	{
		GameObject* dieController = new GameObject();
		dieController->AddComponent<DieController>();
		dieController->SetName(L"DieController");

		AddGameObject(dieController, eLayerType::Default);

		{
			for (int i = 0; i < 7; i++)
			{
				GameObject* const bo = new GameObject();
				bo->AddComponent<SpriteRenderer>();

				
				bo->GetComponent<SpriteRenderer>()->SetColorA(0.55f - 0.08f * i);

				bo->GetComponent<SpriteRenderer>()->SetMaterial(
				gResourceManager->FindOrNull<Material>(L"BlackOut2"));

				bo->GetComponent<Transform>()->SetScale(2.2f + 0.2f * i, 1.2f + 0.2f * i, 1.f);
				bo->GetComponent<SpriteRenderer>()->TurnOffVisiblelity();

				AddGameObject(bo, eLayerType::UI);
				//gKatanaZeroSystem->SetCRTBlackOut(bo);

				dieController->GetComponent<DieController>()->mBlackImages.push_back(bo);
			}			
		}

		//아니...
		{
			float scale = 20.f;
			XMUINT4 color = XMUINT4(109, 178, 255, 200);
			GameObject* text =  InstantiateText(L"아니...", XMUINT2(620, 310), scale, color);
			dieController->GetComponent<DieController>()->mTexts.push_back(text);
			text = InstantiateText(L"통하지 않을 거야.", XMUINT2(570, 333), scale, color);
			dieController->GetComponent<DieController>()->mTexts.push_back(text);
			text = InstantiateText(L"(왼쪽 클릭으로 재시작)", XMUINT2(545, 379), scale, color);
			dieController->GetComponent<DieController>()->mTexts.push_back(text);
		}
	}

	
#pragma endregion	


#pragma region NextScene Effect
	{
		GameObject* const effect = new GameObject();
		effect->AddComponent<SpriteRenderer>();
		effect->AddComponent<NexeScene>();

		effect->GetComponent<SpriteRenderer>()->SetMaterial(
			gResourceManager->FindOrNull<Material>(L"NextScene"));
		effect->GetComponent<SpriteRenderer>()->TurnOnVisiblelity();

		gKatanaZeroSystem->SetNextEffect(effect);

		AddGameObject(effect, eLayerType::Default);
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

#pragma region Enter
	gKatanaZeroSystem->SetCurentScene(this);
#pragma endregion

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

GameObject* KatanaScene::InstantiateText(const wchar_t* wstr, XMUINT2 pos, float scale, XMUINT4 color)
{
	GameObject* const postProcess = new GameObject();

	postProcess->AddComponent<EngineText>();
	postProcess->GetComponent<EngineText>()->SetPosition(pos);
	postProcess->GetComponent<EngineText>()->SetText(wstr);
	postProcess->GetComponent<EngineText>()->SetColor(color);
	postProcess->GetComponent<EngineText>()->SetScale(scale);
	postProcess->GetComponent<EngineText>()->TurnOffVisiblelity();

	postProcess->GetComponent<EngineText>()->TurnOffCamera();

	postProcess->GetComponent<EngineText>()->SetMaterial(
		gResourceManager->FindOrNull<Material>(L"Text"));
	AddGameObject(postProcess, eLayerType::Default);
	return postProcess;
}
