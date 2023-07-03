#pragma once
#include "Singleton.h"
#include "EnumRenderType.h"
#include "Camera.h"

class GameObject;
class Camera;

class RenderManager
{
	friend class Engine;

	SINGLETON_DECLARE(RenderManager);
public:
	void RegisterRenderCamera(const Camera::eCameraType type, Camera* const camera) 
	{
		Assert(type != Camera::eCameraType::End, WCHAR_IS_INVALID_TYPE);
		Assert(camera, WCHAR_IS_NULLPTR);
		Assert(!mCameras[static_cast<UINT>(type)], WCHAR_IS_NOT_NULLPTR);

		mCameras[static_cast<UINT>(type)] = camera; 
	}

	void RegisterRenderGameObject(const eRenderType type, GameObject* const gameObject)
	{
		Assert(gameObject, WCHAR_IS_NULLPTR);

		mRenderObjectArrays[static_cast<UINT>(type)].push_back(gameObject);
	}

	const Camera* GetCurrentCalculateCamera() const
	{
		Assert(mCurrentCalculateCamera, WCHAR_IS_NULLPTR);

		return mCurrentCalculateCamera;
	}

	Camera* GetCamera(const Camera::eCameraType type) const
	{
		Assert(type != Camera::eCameraType::End, WCHAR_IS_INVALID_TYPE);
		Assert(mCameras[static_cast<UINT>(type)], WCHAR_IS_NULLPTR);

		return mCameras[static_cast<UINT>(type)];
	}

private:
	void zSortRenderObjectArray(const eRenderType type);
	void render();
	

private:
	const Camera* mCurrentCalculateCamera;
	Camera* mCameras[static_cast<UINT>(Camera::eCameraType::End)];
	std::vector<GameObject*> mRenderObjectArrays[static_cast<UINT>(eRenderType::End)];	
};
