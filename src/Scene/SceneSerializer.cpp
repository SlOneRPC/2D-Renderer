#include "SceneSerializer.h"
#include <fstream>

void SceneSerializer::SerialiseScene(Scene* scene)
{
	out << YAML::BeginMap;
	out << YAML::Key << "Scene Name" << YAML::Value << "Untitled";
	out << YAML::Key << "Size" << YAML::Value << scene->GetSize();

	SerialiseCamera(scene->GetCamera());
	SerialiseEntities(scene->GetEntityList());

	std::ofstream fout(path);
	fout << out.c_str();
}

template <typename T>
void SceneSerializer::SerialiseComponent(Entity* entity)
{
	if (entity->HasComponent<T>())
	{
		T* component = entity->GetComponent<T>();
		out << YAML::Key << component->GetName() << YAML::Value;
		out << YAML::BeginMap;
		{
			component->Serialise(out);
		}
		out << YAML::EndMap;
	}
}

void SceneSerializer::SerialiseEntities(EntityList& entities)
{
	out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;

	for (std::shared_ptr<Entity>& sharedEnt : entities.GetEntities())
	{
		Entity* entity = sharedEnt.get();

		out << YAML::BeginMap;
		out << YAML::Key << "Entity" << YAML::Value << entity->id;

		SerialiseComponent<TransformComponent>(entity);
		SerialiseComponent<SpriteComponent>(entity);
		SerialiseComponent<QuadComponent>(entity);

		out << YAML::EndMap;
	}

	out << YAML::EndSeq;
}

void SceneSerializer::SerialiseCamera(OrthographicCamera& cam)
{
	out << YAML::Key << "Camera" << YAML::Value;
	out << YAML::BeginMap;
	out << YAML::Key << "Zoom" << -cam.GetZoom();
	out << YAML::EndMap;
}