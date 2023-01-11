#pragma once
#include "Scene/Entity.h"
#include "Core/TimeStep.h"

class MovingEntity : public Entity {
public:
	MovingEntity(int id) : Entity(id) {};

	virtual void OnUpdate(TimeStep ts);

private:
	bool movingLeft = false;
};