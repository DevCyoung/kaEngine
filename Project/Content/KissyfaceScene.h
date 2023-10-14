#pragma once
#include <Engine/Scene.h>

class KissyfaceScene : public Scene
{
public:
	KissyfaceScene();
	virtual ~KissyfaceScene();
	KissyfaceScene(const KissyfaceScene&) = delete;
	KissyfaceScene& operator=(const KissyfaceScene&) = delete;

	virtual void lateUpdate() override final;

	// Scene을(를) 통해 상속됨
	virtual Scene* Clone() override;
};

