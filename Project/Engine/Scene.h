#pragma once
#include "Resource.h"
#include "Layer.h"
#include "EnumLayer.h"
#include <source_location>

class GameObject;

class Scene : public Resource
{
	friend class SceneManager;

private:
	enum class eEventOfScene
	{
		AddGameObject,
		DestroyGameObject,
		End,
	};

	struct tEventMessageScene
	{
		eEventOfScene EventOfSceneType;
		GameObject* EventGameObject;
		eLayerType LayerType;
		std::source_location ErrorHint;
	};

public:
	Scene();
	virtual ~Scene();

	void RegisterEventAddGameObject(GameObject* const gameObject, const eLayerType layerType,
		const std::source_location& location = std::source_location::current());
	void RegisterEventSetDestroy(GameObject* const gameObject,
		const std::source_location& location = std::source_location::current());

	void AddGameObject(GameObject* const gameObject, const eLayerType layerType);

	virtual HRESULT Load(const std::wstring& filePath) override;

private:
	virtual void initialize();
	virtual void update();
	virtual void lateUpdate();

	void eventUpdate();
private:
	Layer mLayers[static_cast<UINT>(eLayerType::End)];

	std::vector<tEventMessageScene> mEventMessages;
	std::vector<GameObject*> mGarbages;
};
