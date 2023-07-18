#pragma once
#include <Engine/Scene.h>

class TItleScene : public Scene
{
public:
	TItleScene();
	virtual ~TItleScene();
	TItleScene(const TItleScene&) = delete;
	TItleScene& operator=(const TItleScene&) = delete;
};

