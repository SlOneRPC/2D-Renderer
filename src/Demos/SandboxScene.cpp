#include "SandboxScene.h"
#include "OpenGL/Texture.h"
#include "MovingEntity.h"

int baseEntId = 0;

void SandboxScene::CreateEntitiy(const glm::vec2& pos, const std::string& texturePath)
{
	std::shared_ptr<Entity> ent = std::make_shared<MovingEntity>(baseEntId++);

	ent->AddComponent<TransformComponent>(pos);
	ent->AddComponent<SpriteComponent>(std::string(BASE_APP_PATH + texturePath));

	ent->GetComponent<TransformComponent>()->scale = glm::vec2(0.2f);

	AddCustomEntity(ent);
}

void SandboxScene::Init()
{
	const float bounds = 8.f;
	const float centre = bounds / 2;

	for (size_t i = 0; i < 100; i++)
	{
		const float randomX = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / bounds))) - centre;
		const float randomY = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / bounds))) - centre;

		glm::vec2 pos(randomX, randomY);

		CreateEntitiy(pos, "images/pacman.png");
	}

	for (size_t i = 0; i < 100; i++)
	{
		const float randomX = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / bounds))) - centre;
		const float randomY = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / bounds))) - centre;

		glm::vec2 pos(randomX, randomY);

		CreateEntitiy(pos, "images/ghost.png");
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
