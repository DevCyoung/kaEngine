#include "pch.h"
#include "Content.h"

#include "TItleScene.h"
#include "Chinatown01Scene.h"
#include "Chinatown04Scene.h"
#include "Chinatown05Scene.h"
#include "HeadHunterScene.h"
#include "TestScene.h"

#include "GameObjectBuilder.h"
#include "MaterialBuilder.h"
#include "ResourceManager.h"

#include <Engine/Engine.h>
#include <Engine/SceneManager.h>
#include <Engine/EngineMath.h>
#include <Engine/TimeManager.h>

#include <Engine/Engine.h>
#include <Engine/GraphicDeviceDx11.h>

Content::Content()
{
	resourceInitialize();

	//Scene* testScene = new Collide2DTestScene;
	//Scene* testScene = new TItleScene();	
	//Scene* testScene = new Chinatown01Scene();
	//Scene* testScene = new Chinatown04Scene();
	Scene* testScene = new Chinatown05Scene();
	//Scene* testScene = new HeadHunterScene();
	//Scene* testScene = new TestScene();

	SceneManager::GetInstance()->LoadScene(testScene);

	TimeManager::initialize();
}

Content::~Content()
{
	TimeManager::deleteInstance();
}

void Content::resourceInitialize()
{
	//Texture* const tex = gResourceManager->Find<Texture>(L"TextureCS");
	//ComputeShader* const cs = gResourceManager->Find<ComputeShader>(L"StdCS");
	//
	//gGraphicDevice->BindCS(cs);
	//gGraphicDevice->BindUAV(0, tex);
	//gGraphicDevice->Distpatch(cs);
	//gGraphicDevice->UnBindUAV(0);


	loadTexture();
	loadShader();
	loadMaterial();	
}

void Content::loadTexture()
{
	for (UINT i = 0; i < static_cast<UINT>(eResTexture::End); ++i)
	{
		gResourceManager->LoadByEnum<Texture>(static_cast<eResTexture>(i));
	}
}

void Content::loadShader()
{

}

void Content::loadMaterial()
{
	//Animation Material
	{
		Material* const material =
			MaterialBuilder::Default2D(
				eRenderPriorityType::Opqaue, L"Animation2D", eResTexture::door);
		gResourceManager->Insert(L"Animation2D", material);
	}

	loadUIMaterial();
}

void Content::loadUIMaterial()
{
	//Cursor
	{
		Material* const material =
			MaterialBuilder::UI2D(
				eRenderPriorityType::Opqaue, eResTexture::UI_spr_cursor);
		gResourceManager->Insert(L"UICursor", material);
	}

	//Hud Bar
	{
		Material* const material =
			MaterialBuilder::UI2D(
				eRenderPriorityType::Opqaue, eResTexture::UI_spr_hud);
		gResourceManager->Insert(L"UIHud", material);
	}

	//Hud Timer
	{

		Material* const material =
			MaterialBuilder::UI2D(
				eRenderPriorityType::Opqaue, eResTexture::UI_spr_hud_timer_0);
		gResourceManager->Insert(L"UIHudTimer", material);
	}

	//Timer
	{

		Material* const material =
			MaterialBuilder::UI2D(
				eRenderPriorityType::Opqaue, eResTexture::UI_spr_timer);
		gResourceManager->Insert(L"UITimer", material);
	}

	//Shift 00
	{
		Material* const material =
			MaterialBuilder::UI2D(
				eRenderPriorityType::Opqaue, eResTexture::UI_spr_keyboard_shift_0);
		gResourceManager->Insert(L"UIShift00", material);
	}

	//Shift 01
	{
		Material* const material =
			MaterialBuilder::UI2D(
				eRenderPriorityType::Opqaue,eResTexture::UI_spr_keyboard_shift_1);
		gResourceManager->Insert(L"UIShift01", material);
	}

	//Battrey
	{
		Material* const material =
			MaterialBuilder::UI2D(
				eRenderPriorityType::Opqaue, eResTexture::UI_spr_hud_battery);
		gResourceManager->Insert(L"UIBattery", material);
	}

	//Battrey part
	{
		Material* const material =
			MaterialBuilder::UI2D(
				eRenderPriorityType::Opqaue, eResTexture::UI_spr_battery_part);
		gResourceManager->Insert(L"UIBatteryPart", material);
	}

	//Hud Item
	{
		Material* const material =
			MaterialBuilder::UI2D(
				eRenderPriorityType::Opqaue, eResTexture::UI_spr_hud_subweapon);
		gResourceManager->Insert(L"UIHudItem", material);
	}

	//Right Item
	{
		Material* const material =
			MaterialBuilder::UI2D(
				eRenderPriorityType::Opqaue, eResTexture::UI_spr_itemicons_0);
		gResourceManager->Insert(L"UIRightItem", material);
	}

	//Left Item
	{
		Material* const material =
			MaterialBuilder::UI2D(
				eRenderPriorityType::Opqaue, eResTexture::UI_spr_katanaicons_0);
		gResourceManager->Insert(L"UILeftItem", material);
	}

	//Right Click Mouse
	{
		Material* const material =
			MaterialBuilder::UI2D(
				eRenderPriorityType::Opqaue, eResTexture::UI_spr_right_click_1);
		gResourceManager->Insert(L"UIRightClick", material);
	}

	//Left Click Mouse
	{
		Material* const material =
			MaterialBuilder::UI2D(
				eRenderPriorityType::Opqaue, eResTexture::UI_spr_left_click_1);
		gResourceManager->Insert(L"UILeftClick", material);
	}
}

void Content::testSceneInitialize()
{
}
