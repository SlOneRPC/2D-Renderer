#include "Alien.h"
#include "Bullet.h"
#include "../SpaceRaidersScene.h"
#include<cstdlib>
#include <GLFW/glfw3.h>

static float lastShot = 0.f;

std::shared_ptr<Entity> Alien::Create(int id, glm::vec2 pos, AlienType type)
{
	auto alien = std::make_shared<Alien>(id);

	const std::string alienFileMap[] = {
		"images/SpaceRaiders/Sprites08.png",
		"images/SpaceRaiders/Sprites04.png",
		"images/SpaceRaiders/Sprites06.png",
		"images/SpaceRaiders/Sprites02.png",
	};

	alien->AddComponent<TransformComponent>(pos, 0, glm::vec2(0.5f));
	alien->AddComponent<SpriteComponent>(alienFileMap[(int)type]);

	return alien;
}

void Alien::OnUpdate(TimeStep ts)
{
	TransformComponent* transform = this->GetComponent<TransformComponent>();

	if (movingLeft) 
	{
		transform->translation.x -= speed * ts;
	}
	else 
	{
		transform->translation.x += speed * ts;
	}

	double time = glfwGetTime();

	if (canShoot && time - lastShot > 1.0f)
	{
		auto bullet = EnemyBullet::Create(SpaceRaidersScene::GetMaxEntityId()++, glm::vec2{ transform->translation.x, transform->translation.y - 0.4 });
		SpaceRaidersScene::GetScene()->AddCustomEntity(bullet);
		lastShot = time;
	}

	canShoot = false;
}

void Alien::SetMoveOpposite(bool moveDown)
{
	if (glfwGetTime() - lastMove > 1.0f) 
	{
		movingLeft = !movingLeft;

		if (!reachedBottom && moveDown)
		{
			auto transform = this->GetComponent<TransformComponent>();
			
			transform->translation.y -= 0.2f;

			lastMove = glfwGetTime();

			speed += 0.1f;

			reachedBottom = transform->translation.y <= -0.1f;
		}
	}
}

void Alien::SetCanShoot(bool canShoot)
{
	this->canShoot = canShoot;
}
