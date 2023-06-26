#pragma once
#include "Scene/Entity.h"
#include "Core/TimeStep.h"

class SpinningEntity : public Entity {
public:
	SpinningEntity(int id) : Entity(id) {};

	inline static std::shared_ptr<Entity> Create(int id) { return std::make_shared<SpinningEntity>(id); }

	virtual void OnUpdate(TimeStep ts);
};