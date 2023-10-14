#pragma once
#include <Engine/Scene.h>

class Chinatown05Scene : public Scene
{
public:
	Chinatown05Scene();
	virtual ~Chinatown05Scene();
	Chinatown05Scene(const Chinatown05Scene&) = delete;
	Chinatown05Scene& operator=(const Chinatown05Scene&) = delete;

	virtual void initialize() override;
	virtual void update() override;

	// Scene을(를) 통해 상속됨
	virtual Scene* Clone() override;
};

