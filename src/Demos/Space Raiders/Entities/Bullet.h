#pragma once
#include "Scene/Entity.h"
#include <memory>

class EnemyBullet : public Entity {
public:
	EnemyBullet(int id) : Entity(id) {};

	inline static std::shared_ptr<Entity> Create(int id) { return std::make_shared<EnemyBullet>(id); }

	static std::shared_ptr<Entity> Create(int id, glm::vec2 pos);

	virtual void OnUpdate(TimeStep ts);
};

class PlayerBullet : public Entity {
public:
	PlayerBullet(int id) : Entity(id) {};

	inline static std::shared_ptr<Entity> Create(int id) { return std::make_shared<PlayerBullet>(id); }

	static std::shared_ptr<Entity> Create(int id, glm::vec2 pos);

	virtual void OnUpdate(TimeStep ts);
};