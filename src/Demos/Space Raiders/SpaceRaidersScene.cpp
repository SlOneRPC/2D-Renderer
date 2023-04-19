#include "SpaceRaidersScene.h"
#include "Core/Random.h"
#include "Entities/EndGame.h"

void SpaceRaidersScene::Init()
{
	instance = this;

	// Spawn Player

	auto rocket = Rocket::Create(entityId++, glm::vec2{ 0, -3.f });
	AddCustomEntity(rocket);
	this->player = (Rocket*)rocket.get();

	// Spawn Enemies

	// -4, 4

	// X X X X
	// X X X X
	// X X X X
	// X X X X


	const float xSize = 8.0f;
	const float gapBetweenEntities = 0.2f;
	const float sizeOfEntity = 0.7f;
	const int entityCount = 6;

	const float finalOverallGap = gapBetweenEntities * entityCount;
	const float finalSize = xSize - finalOverallGap;


	for (float i = 1; i <= 4; i++)
	{
		for (float x = 1; x <= entityCount; x++)
		{
			AlienType type = (AlienType)(i - 1);

			const float posX = (sizeOfEntity * x) - xSize / 4 + x * gapBetweenEntities;
			const float posY = 4.0f - sizeOfEntity * i;

			auto alien = Alien::Create(entityId++, glm::vec2{ posX, posY }, type);
			AddCustomEntity(alien);
			aliens[glm::vec2{ i, x }] = (Alien*)alien.get();
		}
	}

	// Spawn Walls

	const glm::vec2 wallPositions[] = {
		{ 0, -2.2f },
		{ -0.8f, -2.2f},
		{ 0.8f, -2.2f},

		{ -3.5f, -2.2f},
		{ 3.5f, -2.2f},
	};

	for (const glm::vec2& pos : wallPositions) 
	{
		auto wall = Wall::Create(entityId++, pos);
		AddCustomEntity(wall);
	}

	drawList = new ImDrawList(ImGui::GetDrawListSharedData());
}

void SpaceRaidersScene::OnUpdate(TimeStep ts)
{
	const float left = -4.f + 0.25f;
	const float right = 4.f - 0.25f;

	bool hasReachedEdge = false;

	for (auto& entry : aliens) 
	{
		auto transform = entry.second->GetComponent<TransformComponent>();

		if (transform->translation.x <= left || transform->translation.x >= right)
		{
			hasReachedEdge = true;
			break;
		}
	}

	bool reachedBottom = false;

	for (auto& entry : aliens) 
	{
		if (entry.second->reachedBottom) 
		{
			reachedBottom = true;
		}
	}

	if (hasReachedEdge) 
	{
		for (auto& entry : aliens)
		{
			entry.second->SetMoveOpposite(!reachedBottom);
		}
	}

	int random = RandomGenerator::random(6);
	for (int x = 6; x >= 1; x--)
	{
		auto entry = glm::ivec2{ x, random };
		if (aliens.find(entry) != aliens.end())
		{
			aliens[entry]->SetCanShoot(true);
			break;
		}
	}
}

void SpaceRaidersScene::RemoveEntity(Entity* ent)
{
	if (dynamic_cast<Alien*>(ent)) 
	{
		glm::ivec2 key;
		auto& aliens = instance->aliens;
		for (auto& entry : aliens) 
		{
			if (entry.second == ent) 
			{
				key = entry.first;
				break;
			}
		}

		aliens.erase(key);

		if (aliens.size() <= 0)
			instance->EndGame(true);
	}
	else if (dynamic_cast<Wall*>(ent)) 
	{
		auto& walls = instance->walls;
		walls.erase(std::remove_if(walls.begin(), walls.end(), [&](Wall* entity1) { return entity1->id == ent->id;  }), walls.end());
	}
	instance->GetEntityList().DeleteEntity(ent);
}

void SpaceRaidersScene::EndGame(bool win)
{
	auto entities = instance->GetEntityList().GetEntities();

	for (auto& entity : entities) 
	{
		instance->GetEntityList().DeleteEntity(entity.get());
	}

	instance->aliens.clear();
	instance->walls.clear();

	auto endGame = EndGame::Create(SpaceRaidersScene::instance->GetMaxEntityId()++, win);
	instance->AddCustomEntity(endGame);
}

void SpaceRaidersScene::RestartGame()
{
	auto entities = instance->GetEntityList().GetEntities();
	instance->GetEntityList().DeleteEntity(entities[0].get());
	instance->Init();
}

std::unordered_map<glm::ivec2, Alien*>& SpaceRaidersScene::GetAliens()
{
	return SpaceRaidersScene::instance->aliens;
}

std::vector<Wall*>& SpaceRaidersScene::GetWalls()
{
	return SpaceRaidersScene::instance->walls;
}

Rocket* SpaceRaidersScene::GetPlayer()
{
	return SpaceRaidersScene::instance->player;
}

SpaceRaidersScene* SpaceRaidersScene::GetScene()
{
	return SpaceRaidersScene::instance;
}

int& SpaceRaidersScene::GetMaxEntityId()
{
	return SpaceRaidersScene::instance->entityId;
}