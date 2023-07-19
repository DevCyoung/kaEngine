#pragma once

#include <Engine/Scene.h>

class HeadHunterScene : public Scene
{
public:
	HeadHunterScene();
	virtual ~HeadHunterScene();
	HeadHunterScene(const HeadHunterScene&) = delete;
	HeadHunterScene& operator=(const HeadHunterScene&) = delete;
};

