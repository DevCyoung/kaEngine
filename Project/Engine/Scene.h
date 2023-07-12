#pragma once
#include "Resource.h"
#include "Layer.h"
#include "EnumLayer.h"
#include <source_location>

class GameObject;
class RenderTargetRenderer;

struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;

class Scene : public Resource
{
public:
	Scene();
	virtual ~Scene();

	void RegisterEventAddGameObject(GameObject* const gameObject, const eLayerType layerType,
		const std::source_location& location = std::source_location::current());
	void RegisterEventSetDestroy(GameObject* const gameObject,
		const std::source_location& location = std::source_location::current());

	void AddGameObject(GameObject* const gameObject, const eLayerType layerType);

	RenderTargetRenderer* GetRenderTargetRenderer() const { return mRenderTargetRenderer; }

	virtual HRESULT Load(const std::wstring& filePath) override;

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
	virtual void Initialize();
	virtual void Update();
	virtual void LateUpdate();
	//virtual void physicsUpdate
	virtual void Render(const UINT renderTargetWidth,
		const UINT renderTargetHeight,
		const FLOAT backgroundColor[4],
		ID3D11RenderTargetView** const ppRenderTargetView,
		ID3D11DepthStencilView* const depthStencilView) const;

	virtual void RenderFlush();
	virtual void EventUpdate();

private:
	Layer mLayers[static_cast<UINT>(eLayerType::End)];
	std::vector<tEventMessageScene> mEventMessages;
	std::vector<GameObject*> mGarbages;
	RenderTargetRenderer* mRenderTargetRenderer;	
};
