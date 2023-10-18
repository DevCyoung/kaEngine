#include "pch.h"
#include "CCTVTextDrawer.h"
#include "Components.h"
#include <Engine/FontManager.h>

CCTVTextDrawer::CCTVTextDrawer()
    : ScriptComponent(eScriptComponentType::CCTVTextDrawer)
{
}

CCTVTextDrawer::~CCTVTextDrawer()
{
}

void CCTVTextDrawer::initialize()
{
}

void CCTVTextDrawer::update()
{
    FontManager::GetInstance()->DrawFont(L"Àç»ý", 100, 100, 20, 0XFFFFFFFF);
}

void CCTVTextDrawer::lateUpdate()
{
}
