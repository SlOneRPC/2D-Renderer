#include "Rocket.h"
#include "OpenGL/Input.h"
#include "Bullet.h"
#include <GLFW/glfw3.h>

#include <Windows.h>
#include "../SpaceRaidersScene.h"

// Controls
// A & D - MOVE, left, right
// shift - Shoot

std::shared_ptr<Entity> Rocket::Create(int id, glm::vec2 pos)
{
	auto rocket = std::make_shared<Rocket>(id);

	rocket->AddComponent<TransformComponent>(pos, 0, glm::vec2{ 1.f / 2, 1.27f / 2 });
	rocket->AddComponent<SpriteComponent>(BASE_APP_PATH + std::string("images/SpaceRaiders/Sprites00.png"));

	return rocket;
}

void Rocket::OnUpdate(TimeStep ts)
{
	const float movementSpeed = 2.1f;

	if (InputHandler::IsKeyPressed(GLFW_KEY_D)) 
	{
		auto transform = this->GetComponent<TransformComponent>();
		auto newPos = transform->translation.x + movementSpeed * ts;

		if (newPos < 4.f)
		{
			transform->translation.x = newPos;
		}
	}
	else if (InputHandler::IsKeyPressed(GLFW_KEY_A)) 
	{
		auto transform = this->GetComponent<TransformComponent>();
		auto newPos = transform->translation.x - movementSpeed * ts;

		if (newPos > -4.f)
		{
			transform->translation.x = newPos;
		}
	}
	else if (InputHandler::IsKeyPressed(GLFW_KEY_LEFT_SHIFT)) 
	{
		if (glfwGetTime() - lastShotTime > 2.0f) 
		{
			auto transform = this->GetComponent<TransformComponent>();

			auto bullet = PlayerBullet::Create(SpaceRaidersScene::GetMaxEntityId()++, { transform->translation.x, transform->translation.y + transform->scale.y + 0.1f });

			SpaceRaidersScene::GetScene()->AddCustomEntity(bullet);

			PlaySoundA((LPCSTR)(BASE_APP_PATH + std::string("audio/firesound1.wav")).c_str(), NULL, SND_FILENAME | SND_ASYNC);

			lastShotTime = glfwGetTime();
		}
	}
}
