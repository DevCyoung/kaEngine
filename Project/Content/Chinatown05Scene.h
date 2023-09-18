#pragma once
#include "KatanaScene.h"

class Chinatown05Scene : public KatanaScene
{
public:
	Chinatown05Scene();
	virtual ~Chinatown05Scene();
	Chinatown05Scene(const Chinatown05Scene&) = delete;
	Chinatown05Scene& operator=(const Chinatown05Scene&) = delete;

	virtual void initialize() override;
	virtual void update() override;
};

