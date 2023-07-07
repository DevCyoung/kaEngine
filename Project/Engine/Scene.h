#pragma once
#include "Resource.h"
#include "Layer.h"
#include "EnumLayer.h"

class GameObject;


#include <source_location>

//##Event## error	


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

	void AddGameObject(GameObject* const obj, const eLayerType type);

	void RegisterEventAddGameObject(GameObject* const obj, const eLayerType LAYER_TYPE
		, const std::source_location& location = std::source_location::current());

	void RegisterEventSetDestroy(GameObject* const obj, 
		const std::source_location& location = std::source_location::current());

public:
	virtual HRESULT Load(const std::wstring& path) override;

private:
	virtual void initialize();
	virtual void update();
	virtual void lateUpdate();

	void eventUpdate() ;
private:
	Layer mLayers[static_cast<UINT>(eLayerType::End)];

	std::vector<tEventMessageScene> mEventMessages;
	std::vector<GameObject*> mGarbages;
};
