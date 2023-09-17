#pragma once
#include <Engine/Scene.h>
class KatanaScene : public Scene
{
public:
	KatanaScene();
	virtual ~KatanaScene();
	KatanaScene(const KatanaScene&) = delete;
	KatanaScene& operator=(const KatanaScene&) = delete;

	virtual void lateUpdate() override;
};

