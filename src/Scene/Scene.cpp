#include "Scene.h"
#include "imgui.h"
#include "SceneSerializer.h"

Scene::Scene(float size)
	: size(size), entList(EntityList(glm::vec2(0,0), size)), camera(OrthographicCamera(-4, 4, -4, 4))
{
	Init();
	renderer2D = std::make_unique<Renderer2D>();
}

Scene::Scene(const std::string& path)
	: entList(EntityList(glm::vec2(0, 0), 4.f)), camera(OrthographicCamera(-4, 4, -4, 4))
{
	Load(path);
	renderer2D = std::make_unique<Renderer2D>();
}

void Scene::OnUpdate(TimeStep ts)
{
	std::vector<Entity*> ents = entList.GetVisibleEntities(camera);

	// Update entities
	for (Entity* ent : ents) 
	{
		if (entList.GetEntity(ent->id)) 
		{
			glm::vec2 posBefore = ent->GetComponent<TransformComponent>()->translation;

			ent->OnUpdate(ts);

			if (entList.GetEntity(ent->id))
				if (posBefore != ent->GetComponent<TransformComponent>()->translation)
					entList.UpdateEntity(ent);
		}
	}

	// Draw entities
	renderer2D->Begin(camera);
    {
		ents = entList.GetVisibleEntities(camera);
		for (Entity* ent : ents)
		{
			TransformComponent* transformComponent = ent->GetComponent<TransformComponent>();

			if (ent->HasComponent<SpriteComponent>()) 
			{
				SpriteComponent* spriteComponent = ent->GetComponent<SpriteComponent>();
				renderer2D->DrawTexturedQuad(transformComponent->translation, transformComponent->scale, spriteComponent->texture.get(), transformComponent->rotation);
			}
			else
			{
				QuadComponent* quadComponent = ent->GetComponent<QuadComponent>();
				renderer2D->DrawQuad(transformComponent->translation, transformComponent->scale, quadComponent->colour, transformComponent->rotation);
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

int Scene::CreateQuadEntity(const glm::vec2& pos, const Colour& colour, const glm::vec2& scale, float rotation)
{
	std::shared_ptr<Entity> ent = std::make_shared<Entity>(baseId++);

	ent->AddComponent<TransformComponent>(pos, rotation, scale);
	ent->AddComponent<QuadComponent>(colour);

	return entList.AddEntity(ent);
}

int Scene::CreateTexturedEntity(const glm::vec2& pos, const std::string& path, float rotation)
{
	std::shared_ptr<Entity> ent = std::make_shared<Entity>(baseId++);

	ent->AddComponent<TransformComponent>(pos, rotation, glm::vec2{ 1.0f, 1.0f });
	ent->AddComponent<SpriteComponent>(std::string(BASE_APP_PATH + path));

	return entList.AddEntity(ent);
}

int Scene::AddCustomEntity(std::shared_ptr<Entity>& ent)
{
	return entList.AddEntity(ent);
}

void Scene::Save(std::string path)
{
	SceneSerializer serialiser(path);
	serialiser.SerialiseScene(this);
}

void Scene::Load(std::string path)
{
	SceneSerializer serialiser(path);
	serialiser.DeserialiseScene(this);
}

void Scene::Init(float size)
{
	this->size = size;
	entList.RebuildTree(size);
	Init();
}
