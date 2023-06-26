#pragma once

#include "Scene/Entity.h"

class BasicQuadEntity : public Entity {
public:
	BasicQuadEntity(int id) : Entity(id) {};

	inline static std::shared_ptr<Entity> Create(int id) { return std::make_shared<BasicQuadEntity>(id); }

	static std::shared_ptr<Entity> CreateNonTextured(const glm::vec2& pos, const glm::vec2& scale, float rotation, const Colour& colour);
	static std::shared_ptr<Entity> CreateTextured(const glm::vec2& pos, const glm::vec2& scale, float rotation, const std::string& path);

	virtual void OnUpdate(TimeStep ts) { };
};