#include "Scene.h"
#include "imgui.h"


Scene::Scene(float size)
	: size(size), entList(EntityList(glm::vec2(0,0), size)), camera(OrthographicCamera(-4, 4, -4, 4))
{
	Init();
	renderer2D = std::make_unique<Renderer2D>();
}

void Scene::OnUpdate(TimeStep ts)
{
	std::vector<Entity*> ents = entList.GetVisibleEntities(camera);

	// Update entities
	for (Entity* ent : ents) 
	{
		glm::vec2 posBefore = ent->GetComponent<TransformComponent>()->translation;
		ent->OnUpdate(ts);
		if (posBefore != ent->GetComponent<TransformComponent>()->translation) {
			entList.UpdateEntity(ent);
		}
	}

	// Draw entities
	renderer2D->Begin(camera);
    {
		for (Entity* ent : ents)
		{
			if (ent->HasComponent<SpriteComponent>()) 
			{
				TransformComponent* transformComponent = ent->GetComponent<TransformComponent>();
				SpriteComponent* spriteComponent = ent->GetComponent<SpriteComponent>();
				renderer2D->DrawTexturedQuad(transformComponent->translation, transformComponent->scale, spriteComponent->texture.get());
			}
			else
			{
				TransformComponent* transformComponent = ent->GetComponent<TransformComponent>();
				QuadComponent* quadComponent = ent->GetComponent<QuadComponent>();
				renderer2D->DrawQuad(transformComponent->translation, transformComponent->scale, quadComponent->colour);
			}
		}

#ifdef DEBUG
		OnImguiRender();


		glm::vec3 camPosition(camera.GetPosition());
		if (ImGui::DragFloat("Cam x", &camPosition.x)
			|| ImGui::DragFloat("Cam y", &camPosition.y)) {
			camera.SetPosition(camPosition);
		}

		float camZoom = fabsf(camera.GetZoom());
		if (ImGui::DragFloat("Cam zoom", &camZoom)) {
			camera.SetProjection(-camZoom, camZoom, -camZoom, camZoom);
		}

		entList.DrawQuadTree();

#endif // DEBUG
    }
    renderer2D->End();
}


// TEMP
int baseId = 0;

int Scene::CreateQuadEntity(const glm::vec2& pos, const Colour& colour, const glm::vec2& scale)
{
	std::shared_ptr<Entity> ent = std::make_shared<Entity>(baseId++);

	ent->AddComponent<TransformComponent>(pos, 0, scale);
	ent->AddComponent<QuadComponent>(colour);

	return entList.AddEntity(ent);
}

int Scene::CreateTexturedEntity(const glm::vec2& pos, const std::string& path)
{
	std::shared_ptr<Entity> ent = std::make_shared<Entity>(baseId++);
	std::shared_ptr<Texture> texture = std::make_shared<Texture>(BASE_APP_PATH + path);

	ent->AddComponent<TransformComponent>(pos);
	ent->AddComponent<SpriteComponent>(texture);

	return entList.AddEntity(ent);
}

int Scene::AddCustomEntity(std::shared_ptr<Entity>& ent)
{
	return entList.AddEntity(ent);
}
