#include "SandboxScene.h"
#include "OpenGL/Texture.h"
#include "MovingEntity.h"

int baseEntId = 0;

void SandboxScene::CreateEntitiy(const glm::vec2& pos, const std::string& texturePath)
{
	std::shared_ptr<Entity> ent = std::make_shared<MovingEntity>(baseEntId++);

	ent->AddComponent<TransformComponent>(pos, 0, glm::vec2{0.2f});
	ent->AddComponent<SpriteComponent>(std::string(texturePath));

	AddCustomEntity(ent);
}

void SandboxScene::Init()
{
	const float bounds = 8.f;
	const float centre = bounds / 2;

	for (size_t i = 0; i < 200; i++)
	{
		const float randomX = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / bounds))) - centre;
		const float randomY = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / bounds))) - centre;

		glm::vec2 pos(randomX, randomY);

		if (i <= 100)
			CreateEntitiy(pos, "images/pacman.png");
		else
			CreateEntitiy(pos, "images/ghost.png");
	}
}

void SandboxScene::OnUpdate(TimeStep ts)
{
	
}
