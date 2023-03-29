#pragma once
#include "Scene/Scene.h"

class SandboxScene : public Scene {
public:
	SandboxScene(float size) : Scene(size) {};

	void CreateEntitiy(const glm::vec2& pos, const std::string& texturePath);

	virtual void Init();

	virtual void OnUpdate(TimeStep ts);
};