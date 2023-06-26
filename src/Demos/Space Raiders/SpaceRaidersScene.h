#pragma once
#include "Scene/Scene.h"

#include "Entities/Alien.h"
#include "Entities/Rocket.h"
#include "Entities/Wall.h"

#include <glm/gtx/hash.hpp>

class SpaceRaidersScene : public Scene {
public:
	SpaceRaidersScene(float size) : Scene(size) {};

	virtual void Init();

	virtual void OnUpdate(TimeStep ts);

	static void RemoveEntity(Entity* ent);

	static void EndGame(bool win);
	static void RestartGame();

	static std::unordered_map<glm::ivec2, Alien*>& GetAliens();
	static std::vector<Wall*>& GetWalls();
	static Rocket* GetPlayer();
	static SpaceRaidersScene*  GetScene();
	static int& GetMaxEntityId();
private:
	std::unordered_map<glm::ivec2, Alien*> aliens;
	std::vector<Wall*> walls;
	Rocket* player;
	int entityId = 0;

	inline static SpaceRaidersScene* instance;
};
