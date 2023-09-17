#pragma once
#include <Engine/Scene.h>

class Chinatown04Scene : public Scene
{
public:
	Chinatown04Scene();
	virtual ~Chinatown04Scene();
	Chinatown04Scene(const Chinatown04Scene&) = delete;
	Chinatown04Scene& operator=(const Chinatown04Scene&) = delete;

	virtual void lateUpdate() override;

};

