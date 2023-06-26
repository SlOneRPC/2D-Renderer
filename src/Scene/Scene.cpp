#include "Scene.h"
#include "imgui.h"
#include "SceneSerializer.h"
#include "Core/Logging.h"

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

void Scene::BeginScene(TimeStep ts)
{
	renderer2D->Begin(camera);

	// Update inherited scenes
	this->OnUpdate(ts);

	// Perform on update for all entities in the scene
	UpdateEntities(ts);

	// Render entities in the scene
	OnRender();

	ShowFps(ts);

	renderer2D->End();
}


void Scene::UpdateEntities(TimeStep ts)
{
	std::vector<Entity*> ents = entList.GetVisibleEntities(camera);

	// Update entities
	for (Entity* ent : ents)
	{
#ifdef TESTING
		if (!updateFrame) break;
		ts = TimeStep(0.f, 1.f); //timestep should not take any effect
#endif
		if (entList.GetEntity(ent->id))
		{
			glm::vec2 posBefore = ent->GetComponent<TransformComponent>()->translation;

			ent->OnUpdate(ts);

			if (entList.GetEntity(ent->id))
				if (posBefore != ent->GetComponent<TransformComponent>()->translation)
					entList.UpdateEntity(ent);
		}
	}
#ifdef TESTING
	updateFrame = false;
#endif
}

void Scene::OnRender()
{
	std::vector<Entity*> ents = entList.GetVisibleEntities(camera);

	for (Entity* ent : ents)
	{
		TransformComponent* transformComponent = ent->GetComponent<TransformComponent>();

		if (ent->HasComponent<SpriteComponent>())
		{
			SpriteComponent* spriteComponent = ent->GetComponent<SpriteComponent>();
			renderer2D->DrawTexturedQuad(transformComponent->translation, transformComponent->scale, spriteComponent->texture.get(), transformComponent->rotation);
		}
		else if (ent->HasComponent<QuadComponent>())
		{
			QuadComponent* quadComponent = ent->GetComponent<QuadComponent>();
			renderer2D->DrawQuad(transformComponent->translation, transformComponent->scale, quadComponent->colour, transformComponent->rotation);
		}
	}

#if defined(DEBUG) || defined(TESTING)
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

void Scene::ShowFps(TimeStep ts)
{
	bool open = true;

	ImGui::SetNextWindowPos({ 0, 0 });
	ImGui::SetNextWindowSize({ 500, 500 });
	ImGui::Begin("test", &open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs
		| ImGuiWindowFlags_NoBackground);

	ImGui::SetWindowFontScale(1.5f);

	float frameTime = 1.0f / ts;
	const float smoothing = std::pow(0.9, ts * 60 / 1000);
	float lastFrameTime = 1.0f / ts.GetLastFrameDelta();
	float fps = (lastFrameTime * smoothing) + (frameTime * (1.0 - smoothing));

	ImGui::Text((std::string("FPS: ") + std::to_string(fps)).c_str());

	ImGui::End();
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