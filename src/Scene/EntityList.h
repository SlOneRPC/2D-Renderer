#pragma once

#include "glm/vec2.hpp"
#include <vector>
#include <memory>

#include "Entity.h"
#include "QuadTree.h"

#include "OpenGL/OrthographicCamera.h"

class EntityList {
public:
	EntityList(glm::vec2 origin, float size);

	int AddEntity(std::shared_ptr<Entity>& entity);
	void DeleteEntity(int entityId);
	void DeleteEntity(Entity* entity);

	void UpdateEntity(Entity* entity);
	Entity* GetEntity(int entityId);
	std::vector<Entity*> GetVisibleEntities(OrthographicCamera& camera);

	void DrawQuadTree();
	void RebuildTree();
private:
	std::vector<std::shared_ptr<Entity>> entities;
	QuadTree tree;
};