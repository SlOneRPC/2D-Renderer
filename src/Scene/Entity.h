#pragma once
#include <memory>
#include <vector>

#include <iostream>
#include <map>

#include "Core/Colour.h"
#include "Core/TimeStep.h"
#include "../OpenGL/Texture.h"

#include "glm/vec2.hpp"

#define YAML_CPP_API
#define YAML_CPP_DLL
#include "yaml-cpp/yaml.h"
#include <functional>

class Component {
public:
	inline Component(const std::string& name) : name("class " + name) { }
	virtual std::string& GetName() { return name; };
	
	virtual void Serialise(YAML::Emitter& node) {};
private:
	std::string name;
};

class TransformComponent : public Component {
public:
	inline TransformComponent(const glm::vec2& pos, 
							  const float& rotation, 
		                      const glm::vec2& scale)
		: Component("TransformComponent"), translation(pos), rotation(rotation), scale(scale)
		{ }

	inline TransformComponent(const glm::vec2& pos)
		: Component("TransformComponent"), translation(pos)
	{
		rotation = 0;
		scale = glm::vec2(1.0f, 1.0f);
	}

	inline TransformComponent(YAML::Node& node)
		: Component("TransformComponent")
	{
		translation = glm::vec2(node["translation_x"].as<float>(), node["translation_y"].as<float>());
		rotation = node["rotation"].as<float>();
		scale = glm::vec2(node["scale_x"].as<float>(), node["scale_y"].as<float>());
	}

	inline void Serialise(YAML::Emitter& node)
	{
		node << YAML::Key << "translation_x" << YAML::Value << translation.x;
		node << YAML::Key << "translation_y" << YAML::Value << translation.y;

		node << YAML::Key << "rotation" << YAML::Value << rotation;

		node << YAML::Key << "scale_x" << YAML::Value << scale.x;
		node << YAML::Key << "scale_y" << YAML::Value << scale.y;
	}

	glm::vec2 translation;
	float rotation;
	glm::vec2 scale;
};

class SpriteComponent : public Component {
public:

	inline SpriteComponent(const std::string& path)
		: Component("SpriteComponent"), path(path), texture(std::make_shared<Texture>(path))
		{ }

	inline SpriteComponent(YAML::Node& node)
		: Component("SpriteComponent")
	{
		path = node["TextureLocation"].as<std::string>();
		texture = std::make_shared<Texture>(path);
	}

	inline void Serialise(YAML::Emitter& node)
	{
		node << YAML::Key << "TextureLocation" << YAML::Value << path;
	}

	std::string path;
	std::shared_ptr<Texture> texture;
};

class QuadComponent : public Component {
public:

	inline QuadComponent(const Colour& colour)
		: Component("QuadComponent"), colour(colour)
		{ }

	inline QuadComponent(YAML::Node& node)
		: Component("QuadComponent")
	{
		colour = {
			node["colour_r"].as<float>(),
			node["colour_g"].as<float>(),
			node["colour_b"].as<float>(),
			node["colour_a"].as<float>()
		};
	}

	inline void Serialise(YAML::Emitter& node)
	{
		node << YAML::Key << "colour_r" << YAML::Value << colour.r;
		node << YAML::Key << "colour_g" << YAML::Value << colour.g;
		node << YAML::Key << "colour_b" << YAML::Value << colour.b;
		node << YAML::Key << "colour_a" << YAML::Value << colour.a;
	}

	Colour colour;
};

class Entity {
public:
	Entity(int id) : id(id) {};

	int id;

	inline static std::shared_ptr<Entity> Create(int id) { return std::make_shared<Entity>(id); }

	virtual void OnCreate() {};
	virtual void OnUpdate(TimeStep ts) {};

	bool operator==(Entity e) { return e.id == this->id; };

	template <typename T>
	T* GetComponent() {
		for (std::shared_ptr<Component>& component : components) {
			if (T* outcome = dynamic_cast<T*>(component.get())) {
				return outcome;
			}
		}
		return nullptr;
	}

	template <typename T>
	bool HasComponent() {
		for (std::shared_ptr<Component>& component : components) {
			if (dynamic_cast<T*>(component.get())) {
				return true;
			}
		}
		return false;
	}

	template <typename T>
	bool IsEntityType() {
		return dynamic_cast<T*>(this);
	}

	template <typename T, typename... Args>
	void AddComponent(Args&&... args)
	{
		components.push_back(std::make_shared<T>(T(std::forward<Args>(args)...)));
	}

private:
	std::vector<std::shared_ptr<Component>> components;
};


typedef std::shared_ptr<Entity> (*FactoryType)(int id);
inline std::map<std::string, FactoryType> entityTypeMap;

template <typename T>
inline void RegisterEntity() 
{
	auto name = typeid(T).name();
	
	entityTypeMap[std::string(name)] = T::Create;
}