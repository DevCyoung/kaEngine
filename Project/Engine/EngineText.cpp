#include "pch.h"
#include "EngineText.h"
#include "FontManager.h"
#include "ResourceManager.h"
#include "Material.h"
#include "Mesh.h"
#include "Transform.h"
#include "Camera.h"
EngineText::EngineText()
	: RenderComponent(eComponentType::EngineText)
	, mText(L"")
	, mPosition{}
	, mScale{20}
	, mColor(XMUINT4(255,255,255,255))
{
	SetMaterial(gResourceManager->FindOrNull<Material>(L"Animation2D"));
	SetMesh(gResourceManager->FindOrNull<Mesh>(L"FillRect2D"));
}

EngineText::~EngineText()
{
}

void EngineText::initialize()
{
}

void EngineText::update()
{
	RenderComponent::update();
}

void EngineText::lateUpdate()
{
}

void EngineText::render(const Camera* const camera)
{
	(void)camera;

	Vector3 position = camera->GetOwner()->GetComponent<Transform>()->GetWorldMatrix().Translation();

	UINT color = FONT_RGBA(mColor.x, mColor.y, mColor.z, mColor.w);
	float x = static_cast<float>(mPosition.x) + position.x;
	float y = static_cast<float>(mPosition.y) + position.y;
	FontManager::GetInstance()->DrawFont(mText.c_str(), x, y, mScale, color);
}
