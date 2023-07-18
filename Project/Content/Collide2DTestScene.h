#pragma once
#include <Engine/Scene.h>

class Collide2DTestScene : public Scene
{
public:
	Collide2DTestScene();
	virtual ~Collide2DTestScene();
	Collide2DTestScene(const Collide2DTestScene&) = delete;
	Collide2DTestScene& operator=(const Collide2DTestScene&) = delete;

};

