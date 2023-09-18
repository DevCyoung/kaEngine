#pragma once

#include <Engine/Scene.h>
class Chinatown01Scene : public Scene
{
public:
	Chinatown01Scene();
	virtual ~Chinatown01Scene();
	Chinatown01Scene(const Chinatown01Scene&) = delete;
	Chinatown01Scene& operator=(const Chinatown01Scene&) = delete;

	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
};

