#pragma once
#include "Scene/Scene.h"

/* Class for serialising a scene using yaml for cpp. The reason for this being it's human readable */		
class SceneSerializer {
public:
	SceneSerializer(std::string& path) : path(BASE_APP_PATH + std::string("saves/") + path) {}
	
	void SerialiseScene(Scene* scene);
	bool DeserialiseScene(Scene* scene);
private:
	template <typename T>
	void SerialiseComponent(Entity* entity);

	template <typename T>
	void DeserialiseComponent(Entity* entity, YAML::detail::iterator_value& node);

	void SerialiseEntities(EntityList& entities);
	void SerialiseCamera(OrthographicCamera& cam);
	
	YAML::Emitter out;
	std::string path;
};