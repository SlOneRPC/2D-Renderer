#include "Wall.h"

std::shared_ptr<Entity> Wall::Create(int id, glm::vec2 pos)
{
    auto wall = std::make_shared<Wall>(id);

    wall->AddComponent<TransformComponent>(pos, 0, glm::vec2(0.5f));
    wall->AddComponent<SpriteComponent>(std::string("images/SpaceRaiders/Sprites10.png"));

    return wall;
}

void Wall::OnUpdate(TimeStep ts)
{

}
