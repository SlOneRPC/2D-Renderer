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
    std::remove_if(entities.begin(), entities.end(), [&](std::shared_ptr<Entity> entity) { 
        if (entity->id == entityId) {
            tree.RemoveEntity(entity.get());
            return true;
        }
        return false;
    });
}

void EntityList::DeleteEntity(Entity* entity)
{
    assert(entity);
    std::remove_if(entities.begin(), entities.end(), [&](std::shared_ptr<Entity> entity1) { return entity1->id == entity->id;  });
    tree.RemoveEntity(entity);
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

void EntityList::DrawQuadTree()
{
    if (ImGui::Button("Recreate quad tree")) 
    {
        RebuildTree();
    }
    tree.Draw();
}

void EntityList::RebuildTree()
{
    tree.Recreate();

    for (std::shared_ptr<Entity>& ent : entities) 
    {
        tree.AddEntity(ent.get());
    }
}
