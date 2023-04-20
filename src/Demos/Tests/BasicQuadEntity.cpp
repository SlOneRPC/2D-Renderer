#include "BasicQuadEntity.h"

std::shared_ptr<Entity> BasicQuadEntity::CreateNonTextured(const glm::vec2& pos, const glm::vec2& scale, float rotation, const Colour& colour)
{
	std::shared_ptr<Entity> ent = std::make_shared<Entity>();

	ent->AddComponent<TransformComponent>(pos, rotation, scale);
	ent->AddComponent<QuadComponent>(colour);

	return ent;
}

std::shared_ptr<Entity> BasicQuadEntity::CreateTextured(const glm::vec2& pos, const glm::vec2& scale, float rotation, const std::string& path)
{
	std::shared_ptr<Entity> ent = std::make_shared<Entity>();

	ent->AddComponent<TransformComponent>(pos, rotation, glm::vec2{ 1.0f, 1.0f });
	ent->AddComponent<SpriteComponent>(std::string(path));

	return ent;
}