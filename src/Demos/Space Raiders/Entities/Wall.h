#pragma once
#include "Scene/Entity.h"
#include <memory>

class Wall : public Entity {
public:
	Wall(int id) : Entity(id) {};

	inline static std::shared_ptr<Entity> Create(int id) { return std::make_shared<Wall>(id); }

	static std::shared_ptr<Entity> Create(int id, glm::vec2 pos);

	virtual void OnUpdate(TimeStep ts);

	int health = 2;
};