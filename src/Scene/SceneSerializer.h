#pragma once
#include "Scene/Scene.h"

/* Class for serialising a scene using yaml for cpp. The reason for this being it's human readable */		
class SceneSerializer {
public:
	SceneSerializer(std::string& path) : path(path) {}
	void SerialiseScene(Scene* scene);
private:
	template <typename T>
	void SerialiseComponent(Entity* entity);

	void SerialiseEntities(EntityList& entities);
	void SerialiseCamera(OrthographicCamera& cam);
	
	YAML::Emitter out;
	std::string path;
};