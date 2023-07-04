#pragma once
#include "Resource.h"
#include "Layer.h"
#include "EnumLayer.h"

class GameObject;

class Scene : public Resource
{	
	friend class SceneManager;
public:
	Scene();
	virtual ~Scene();

	void AddGameObject(GameObject* const obj, const eLayerType type);

public:
	virtual void initialize();
	virtual void update();
	virtual void lateUpdate();

public:
	virtual HRESULT Load(const std::wstring& path) override;

private:
	Layer mLayers[static_cast<UINT>(eLayerType::End)];
};
