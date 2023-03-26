#pragma once
#include "Scene/Entity.h"
#include "Core/TimeStep.h"

class MovingEntity : public Entity {
public:
	MovingEntity(int id) : Entity(id) {};

	inline static std::shared_ptr<Entity> Create(int id) { return std::make_shared<MovingEntity>(id); }

	virtual void OnUpdate(TimeStep ts);

private:
	bool movingLeft = false;
};