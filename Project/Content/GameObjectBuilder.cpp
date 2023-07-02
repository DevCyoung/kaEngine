#include "pch.h"
#include "GameObjectBuilder.h"
#include "Components.h"
#include "ResourceManager.h"

GameObject* GameObjectBuilder::BuildDefault2DGameObject(const std::wstring& materialName)
{
	GameObject* const obj = new GameObject();
	obj->AddComponent<MeshRenderer>();

	MeshRenderer* const meshRenderer = obj->GetComponent<MeshRenderer>();
	meshRenderer->SetMesh(gResourceManager->FindOrNullByRelativePath<Mesh>(L"Rect"));
	meshRenderer->SetMaterial(gResourceManager->FindOrNullByRelativePath<Material>(materialName));
	return obj;
}
