#pragma once
#include "Scene/Scene.h"

class SandboxScene : public Scene {
public:
	SandboxScene(float size) : Scene(size) {};

	virtual void Init();

	virtual void OnUpdate(TimeStep ts);
};