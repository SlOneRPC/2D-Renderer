#pragma once
#include "EntityList.h"
#include "Renderer/Renderer2D.h"
#include "Core/TimeStep.h"

class Scene {
public:
	Scene(float size);
	Scene(const std::string& path);

	void BeginScene(TimeStep ts);

	virtual void OnUpdate(TimeStep ts) {};

	virtual void OnImguiRender() {};

	int AddCustomEntity(std::shared_ptr<Entity>& ent);

	void Save(std::string path);
	void Load(std::string path);

	EntityList& GetEntityList() { return entList;  };
	OrthographicCamera& GetCamera() { return camera;  };
	float GetSize() { return size; }

	void Init(float size);
	virtual void Init() {};
protected:
	void UpdateEntities(TimeStep ts);
	void OnRender();
	void ShowFps(TimeStep ts);


	float size;
	EntityList entList;
	OrthographicCamera camera;
	std::unique_ptr<Renderer2D> renderer2D;
};

#ifdef TESTING
inline bool updateFrame = false;
#endif
