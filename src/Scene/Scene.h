#pragma once
#include "EntityList.h"
#include "Renderer/Renderer2D.h"
#include "Core/TimeStep.h"

class Scene {
public:
	Scene(float size);

	virtual void OnUpdate(TimeStep ts);

	virtual void OnImguiRender() {};

	int CreateQuadEntity(const glm::vec2& pos, const Colour& colour, const glm::vec2& scale = glm::vec2(1.0f, 1.0f));
	int CreateTexturedEntity(const glm::vec2& pos, const std::string& path);
	int AddCustomEntity(std::shared_ptr<Entity>& ent);

	void Save(std::string path);
	void Load(std::string& path);

	EntityList& GetEntityList() { return entList;  };
	OrthographicCamera& GetCamera() { return camera;  };
	float GetSize() { return size; }
protected:
	virtual void Init() {};

	float size;
	EntityList entList;
	OrthographicCamera camera;
	std::unique_ptr<Renderer2D> renderer2D;
};