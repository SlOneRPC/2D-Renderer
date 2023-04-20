#include "EntityList.h"
#include "OpenGL/OrthographicCamera.h"

// TEMP
#include "Renderer/Renderer2D.h"
#include "imgui.h"

EntityList::EntityList(glm::vec2 origin, float size)
    : tree(QuadTree(origin, size))
{
    
}

int EntityList::AddEntity(std::shared_ptr<Entity>& entity)
{
    entities.push_back(entity);
    tree.AddEntity(entity.get());
    return entity->id;
}

void EntityList::DeleteEntity(int entityId)
{
    entities.erase(std::remove_if(entities.begin(), entities.end(), [&](std::shared_ptr<Entity> entity) {
        if (entity->id == entityId) {
            tree.RemoveEntity(entity.get());
            return true;
        }
        return false;
    }), entities.end());
}

void EntityList::DeleteEntity(Entity* entity)
{
    assert(entity);
    tree.RemoveEntity(entity);
    entities.erase(std::remove_if(entities.begin(), entities.end(), [&](std::shared_ptr<Entity> entity1) { return entity1->id == entity->id;  }), entities.end());
}

void EntityList::UpdateEntity(Entity* entity)
{
    tree.MoveEntity(entity);
}

Entity* EntityList::GetEntity(int entityId)
{
    for (std::shared_ptr<Entity>& ent : entities) {
        if (ent->id == entityId) {
            return ent.get();
        }
    }
    return nullptr;
}

std::vector<Entity*> EntityList::GetVisibleEntities(OrthographicCamera& camera)
{
    return tree.GetEntities(camera.GetZoom() + camera.GetPosition(), fabsf(camera.GetZoom()) - camera.GetPosition());
}

std::vector<std::shared_ptr<Entity>> EntityList::GetEntities()
{
    return entities;
}

std::vector<Entity*> EntityList::GetCollidingEntities(Entity* other)
{
    return tree.GetCollidingEntities(other);
}

void EntityList::DrawQuadTree()
{
#ifdef DEBUG
    if (ImGui::Button("Recreate quad tree")) 
    {
        RebuildTree();
    }
#endif
    tree.Draw();
}

void EntityList::RebuildTree(float size)
{
    tree.Recreate(size);

    for (std::shared_ptr<Entity>& ent : entities) 
    {
        tree.AddEntity(ent.get());
    }
}
