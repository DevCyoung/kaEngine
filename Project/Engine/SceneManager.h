#include "Singleton.h"
#include "Scene.h"

struct ID3D11DepthStencilView;
struct ID3D11RenderTargetView;

class SceneManager
{
	friend class Engine;
	SINGLETON_DECLARE(SceneManager);

public:
	void LoadScene(Scene* const scene);
	Scene* GetCurrentScene() const { Assert(mCurrentScene, WCHAR_IS_NULLPTR); return mCurrentScene; }



private:
	void update();
	void lateUpdate();
	void eventUpdate();
	void render(const UINT renderTargetWidth,
		const UINT renderTargetHeight,
		const FLOAT backgroundColor[4],
		ID3D11RenderTargetView** const ppRenderTargetView,
		ID3D11DepthStencilView* const depthStencilView);

private:
	Scene* mCurrentScene;	
};

#define gCurrentScene SceneManager::GetInstance()->GetCurrentScene()
