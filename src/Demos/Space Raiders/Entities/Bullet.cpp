#include "Bullet.h"
#include "../SpaceRaidersScene.h"
#include "Core/Logging.h"

std::shared_ptr<Entity> PlayerBullet::Create(int id, glm::vec2 pos)
{
	auto bullet = std::make_unique<PlayerBullet>(id);

	bullet->AddComponent<TransformComponent>(pos, 0, glm::vec2{ 0.1f, 0.1f * 1.75 });
	bullet->AddComponent<SpriteComponent>(BASE_APP_PATH + std::string("images/SpaceRaiders/Sprites01.png"));

	return bullet;
}

void PlayerBullet::OnUpdate(TimeStep ts)
{
	const float bulletSpeed = 1.5f;

	auto transform = this->GetComponent<TransformComponent>();

	transform->translation.y += bulletSpeed * ts;

	auto collidingEntites = SpaceRaidersScene::GetScene()->GetEntityList().GetCollidingEntities(this);

	for (Entity* ent : collidingEntites) 
	{
		if (ent != this)
		{
			if (ent->IsEntityType<Alien>() || ent->IsEntityType<EnemyBullet>())
			{
				PlaySoundA((LPCSTR)(BASE_APP_PATH + std::string("audio/EnemyDeathSound1.wav")).c_str(), NULL, SND_FILENAME | SND_ASYNC);

				SpaceRaidersScene::GetScene()->RemoveEntity(ent);
				SpaceRaidersScene::GetScene()->RemoveEntity(this);
				return;
			}
			else if (ent->IsEntityType<Wall>())
			{
				SpaceRaidersScene::GetScene()->RemoveEntity(this);
				return;
			}
		}
	}

	if (transform->translation.y > 4.f)
	{
		SpaceRaidersScene::RemoveEntity(this);
	}
}

std::shared_ptr<Entity> EnemyBullet::Create(int id, glm::vec2 pos)
{
	auto bullet = std::make_unique<EnemyBullet>(id);

	bullet->AddComponent<TransformComponent>(pos, 180, glm::vec2{ 0.1f, 0.1f * 1.75 });
	bullet->AddComponent<SpriteComponent>(BASE_APP_PATH + std::string("images/SpaceRaiders/Sprites03.png"));

	return bullet;
}

void EnemyBullet::OnUpdate(TimeStep ts)
{
	const float bulletSpeed = 3.5f;

	auto transform = this->GetComponent<TransformComponent>();

	transform->translation.y -= bulletSpeed * ts;

	auto collidingEntites = SpaceRaidersScene::GetScene()->GetEntityList().GetCollidingEntities(this);

	for (Entity* ent : collidingEntites)
	{
		if (ent != this)
		{
			if (ent->IsEntityType<Wall>())
			{
				auto wall = (Wall*)ent;

				wall->health--;
				if (wall->health <= 0) 
				{
					SpaceRaidersScene::GetScene()->RemoveEntity(ent);
				}
				SpaceRaidersScene::GetScene()->RemoveEntity(this);
				return;
			}
			else if (ent->IsEntityType<Rocket>())
			{
				SpaceRaidersScene::GetScene()->EndGame(false);
				return;
			}
		}
	}

	if (transform->translation.y < -4.f) 
	{
		SpaceRaidersScene::RemoveEntity(this);
	}
}
