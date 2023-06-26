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

	void SetMoveOpposite(bool moveDown = true);
	void SetCanShoot(bool canShoot);

	bool reachedBottom = false;
private:
	bool movingLeft = false;
	bool canShoot = false;
	float cooldown = 0.0f;
	float lastMove = 0.0f;
	float speed = 0.4f;
};