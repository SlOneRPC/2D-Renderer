#pragma once
#include "Scene/Entity.h"
#include <memory>

class EndGame : public Entity 
{
public:
	EndGame(int id) : Entity(id) {};

	inline static std::shared_ptr<Entity> Create(int id) { return std::make_shared<EndGame>(id); }

	static std::shared_ptr<Entity> Create(int id, bool win);

	virtual void OnUpdate(TimeStep ts);
};