#pragma once
#include "Scene/Entity.h"
#include <memory>

enum class AlienType {
	purple,
	red,
	orange,
	green
};

class Alien : public Entity {
public:
	Alien(int id) : Entity(id) {};

	inline static std::shared_ptr<Entity> Create(int id) { return std::make_shared<Alien>(id); }

	static std::shared_ptr<Entity> Create(int id, glm::vec2 pos, AlienType type = AlienType::purple);

	virtual void OnUpdate(TimeStep ts);

	void SetMoveOpposite();
	void SetCanShoot(bool canShoot);
private:
	bool movingLeft = false;
	bool canShoot = false;
	float cooldown = 0.0f;
	float lastMove = 0.0f;
};