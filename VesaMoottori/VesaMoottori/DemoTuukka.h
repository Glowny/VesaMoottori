#pragma once
#include "ResourceManager.h"

class DemoTuukka
{
public:
	DemoTuukka() : running(true) {};
	~DemoTuukka() {};
	void TuukkaScene();
	void CloseScene() { running = false; }

private:
	bool running;
	ResourceManager R;
};