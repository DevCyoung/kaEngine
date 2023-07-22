#include "pch.h"
#include "GameObjectBuilder.h"
#include "Components.h"
#include "ResourceManager.h"
#include <Engine/Engine.h>

GameObject* GameObjectBuilder::BuildDefault2DGameObject(const std::wstring& materialName)
{
	GameObject* const obj = new GameObject();
	obj->AddComponent<SpriteRenderer>();

	SpriteRenderer* const spriteRenderer = obj->GetComponent<SpriteRenderer>();
	spriteRenderer->SetMesh(gResourceManager->FindOrNull<Mesh>(L"FillRect2D"));
	spriteRenderer->SetMaterial(gResourceManager->FindOrNull<Material>(materialName));

	return obj;
}
