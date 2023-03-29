#pragma once
#include "Scene/Entity.h"

class Rocket : public Entity {
public:
	Rocket(int id) : Entity(id) {};

	inline static std::shared_ptr<Entity> Create(int id) { return std::make_shared<Rocket>(id); }

	static std::shared_ptr<Entity> Create(int id, glm::vec2 pos);

	virtual void OnUpdate(TimeStep ts);
private:
	double lastShotTime = 0;
};