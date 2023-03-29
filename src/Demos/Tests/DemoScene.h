#pragma once
#include "Scene/Scene.h"

class BasicDemoScene : public Scene {
public:
	BasicDemoScene(float size) : Scene(size) {};

	virtual void Init();
};