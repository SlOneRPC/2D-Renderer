#include "SceneSerializer.h"
#include "Core/Logging.h"
#include <fstream>
#include <typeinfo>

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

bool SceneSerializer::DeserialiseScene(Scene* scene)
{
	YAML::Node data;

	try 
	{
		data = YAML::LoadFile(path);
	}
	catch (YAML::ParserException e) {
		LOG_ERROR("Failed to load scene file -> " + path +
			"\nFile error -> " + std::string(e.what()));
		return false;
	}
		
	std::string sceneName = data["Scene Name"].as<std::string>();
	LOG_INFO("Loading scene " + sceneName);

	scene->Init(data["Size"].as<float>());

	auto entities = data["Entities"];
	if (entities) 
	{
		for (auto ent : entities) 
		{
			int id = ent["Entity"].as<int>();
			auto type = ent["Type"].as<std::string>();

			if (entityTypeMap.find(type) != entityTypeMap.end())
			{
				std::shared_ptr<Entity> deserialisedEntity = entityTypeMap[type](id);

				DeserialiseComponent<TransformComponent>(deserialisedEntity.get(), ent);
				DeserialiseComponent<SpriteComponent>(deserialisedEntity.get(), ent);
				DeserialiseComponent<QuadComponent>(deserialisedEntity.get(), ent);

				scene->AddCustomEntity(deserialisedEntity);
			}
			else 
			{
				LOG_INFO("Missing entity type!!");
				assert(false);
			}
		}
	}

	float zoom = data["Camera"]["Zoom"].as<float>();
	scene->GetCamera() = OrthographicCamera(-zoom, zoom, -zoom, zoom);
	scene->GetCamera().SetPosition({ data["Camera"]["Position_x"].as<float>(), data["Camera"]["Position_y"].as<float>(), 0.f });
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

template<typename T>
void SceneSerializer::DeserialiseComponent(Entity* entity, YAML::detail::iterator_value& node)
{
	auto name = typeid(T).name();
	if (node[name])
	{
		auto test = node[name];
		entity->AddComponent<T>(test);
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
		out << YAML::Key << "Type" << YAML::Value << typeid(*entity).name();

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
	out << YAML::Key << "Zoom" << YAML::Value << -cam.GetZoom();
	out << YAML::Key << "Position_x" << YAML::Value << cam.GetPosition().x;
	out << YAML::Key << "Position_y" << YAML::Value << cam.GetPosition().y;
	out << YAML::EndMap;
}