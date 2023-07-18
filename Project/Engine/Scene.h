#pragma once
#include "Resource.h"
#include "Layer.h"
#include "EnumLayer.h"

#include <source_location>

class GameObject;
class RenderTargetRenderer;
class CollisionManagement2D;

struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;

class Scene : public Resource
{
	friend class SceneManager;
	friend class CollisionManagement2D;

public:
	Scene();
	virtual ~Scene();

	void RegisterEventAddGameObject(GameObject* const gameObject, const eLayerType layerType,
		const std::source_location& location = std::source_location::current());
	void RegisterEventSetDestroy(GameObject* const gameObject,
		const std::source_location& location = std::source_location::current());

	void AddGameObject(GameObject* const gameObject, const eLayerType layerType);

	RenderTargetRenderer* GetRenderTargetRenderer() const { return mRenderTargetRenderer; }
	CollisionManagement2D* GetCollisionManagement2D() const { return mCollisionManagement2D; }

	virtual HRESULT Load(const std::wstring& filePath) override;

	const Vector4& GetBackgroundColor() const { return mBackgroundColor; }
	void SetBackgroundColor(const Vector4& color) { mBackgroundColor = color; }


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

private:
	virtual void initialize();
	virtual void update();
	virtual void lateUpdate();
	//virtual void physicsUpdate
	virtual void render(const UINT renderTargetWidth,
		const UINT renderTargetHeight,
		ID3D11RenderTargetView** const ppRenderTargetView,
		ID3D11DepthStencilView* const depthStencilView) const;

	virtual void renderFlush();
	virtual void eventUpdate();

protected:
	CollisionManagement2D* mCollisionManagement2D;

private:
	Layer mLayers[static_cast<UINT>(eLayerType::End)];
	std::vector<tEventMessageScene> mEventMessages;
	std::vector<GameObject*> mGarbages;
	RenderTargetRenderer* mRenderTargetRenderer;	
	Vector4 mBackgroundColor;
};
