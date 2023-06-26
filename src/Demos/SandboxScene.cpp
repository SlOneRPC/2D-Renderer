#include "SandboxScene.h"
#include "OpenGL/Texture.h"
#include "MovingEntity.h"

void SandboxScene::Init()
{
	const float bounds = 8.f;
	const float centre = bounds / 2;

	int baseId = 0;
	for (size_t i = 0; i < 100; i++)
	{
		std::shared_ptr<Entity> ent = std::make_shared<MovingEntity>(baseId++);
		std::shared_ptr<Texture> texture = std::make_shared<Texture>(BASE_APP_PATH + std::string("images/pacman.png"));

		const float randomX = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / bounds))) - centre;
		const float randomY = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / bounds))) - centre;

		glm::vec2 pos(randomX, randomY);

		ent->AddComponent<TransformComponent>(pos);
		ent->AddComponent<SpriteComponent>(texture);

		ent->GetComponent<TransformComponent>()->scale = glm::vec2(0.2f);

		AddCustomEntity(ent);
	}

	for (size_t i = 0; i < 100; i++)
	{
		std::shared_ptr<Entity> ent = std::make_shared<MovingEntity>(baseId++);
		std::shared_ptr<Texture> texture = std::make_shared<Texture>(BASE_APP_PATH + std::string("images/ghost.png"));

		const float randomX = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / bounds))) - centre;
		const float randomY = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / bounds))) - centre;

		glm::vec2 pos(randomX, randomY);

		ent->AddComponent<TransformComponent>(pos);
		ent->AddComponent<SpriteComponent>(texture);
		ent->GetComponent<TransformComponent>()->scale = glm::vec2(0.2f);

		AddCustomEntity(ent);
	}
}

void SandboxScene::OnUpdate(TimeStep ts)
{
	Scene::OnUpdate(ts);

	//std::vector<Entity*> ents = entList.GetVisibleEntities(camera);

	//// Update entities
	//for (Entity* ent : ents)
	//{
	//	ent->OnUpdate(ts);
	//}
}
