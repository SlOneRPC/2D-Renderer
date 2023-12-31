#include "EndGame.h"
#include "OpenGL/Input.h"
#include "Application.h"
#include <GLFW/glfw3.h>
#include "../SpaceRaidersScene.h"

std::shared_ptr<Entity> EndGame::Create(int id, bool win)
{
	auto endGame = std::make_shared<EndGame>(id);

	endGame->AddComponent<TransformComponent>(glm::vec2{ 0.0f, 0.0f }, 0, glm::vec2 { 8.0f, 8.0f * 0.8f });
	endGame->AddComponent<SpriteComponent>(std::string(win ? "images/SpaceRaiders/WinScreen.png" : "images/SpaceRaiders/LoseScreen.png"));

	return endGame;
}

void EndGame::OnUpdate(TimeStep ts)
{
	if (InputHandler::IsKeyPressed(GLFW_KEY_SPACE)) 
	{
		SpaceRaidersScene::GetScene()->RestartGame();
	}
	else if (InputHandler::IsKeyPressed(GLFW_KEY_ESCAPE)) 
	{
		glfwSetWindowShouldClose(g_window->GetGlFWWindow(), GL_TRUE);
	}
}
