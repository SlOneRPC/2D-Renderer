#include "pch.h"
#include "Scene/EntityList.h"

TEST(EntityListTests, EnsureEntityListCanBeCreated) {

	EntityList entList({0,0}, 8.f);
}

TEST(EntityListTests, EnsureEntityListCanStoreEntities) {

	EntityList entList({ 0,0 }, 8.f);

	std::shared_ptr<Entity> ent = std::make_shared<Entity>(99);
	ent->AddComponent<TransformComponent>(glm::vec2{0,0});

	entList.AddEntity(ent);

	EXPECT_EQ(ent.get(), entList.GetEntity(99));
}

TEST(EntityListTests, EnsureEntityListCanDeleteEntities) {

	EntityList entList({ 0,0 }, 8.f);

	std::shared_ptr<Entity> ent = std::make_shared<Entity>(99);
	ent->AddComponent<TransformComponent>(glm::vec2{ 0,0 });

	entList.AddEntity(ent);

	EXPECT_EQ(ent.get(), entList.GetEntity(99));

	entList.DeleteEntity(ent.get());

	EXPECT_EQ(nullptr, entList.GetEntity(99));
}

TEST(EntityListTests, EnsureEntityListCanDeleteEntitiesById) {

	EntityList entList({ 0,0 }, 8.f);

	std::shared_ptr<Entity> ent = std::make_shared<Entity>(99);
	ent->AddComponent<TransformComponent>(glm::vec2{ 0,0 });

	entList.AddEntity(ent);

	EXPECT_EQ(ent.get(), entList.GetEntity(99));

	entList.DeleteEntity(ent.get()->id);

	EXPECT_EQ(nullptr, entList.GetEntity(99));
}

TEST(EntityListTests, EnsureEntityListReturnsCorrectEntitiesInScreenSpace) {

	EntityList entList({ 0,0 }, 8.f);

	std::shared_ptr<Entity> ent = std::make_shared<Entity>(99);
	ent->AddComponent<TransformComponent>(glm::vec2{ 0,0 });

	entList.AddEntity(ent);

	OrthographicCamera cam(-4, 4, -4, 4);

	EXPECT_EQ(ent.get(), entList.GetVisibleEntities(cam)[0]);
}

TEST(EntityListTests, EnsureEntityListReturnsDoesNotReturnEntityNotInScreenSpace) {

	EntityList entList({ 0,0 }, 8.f);

	std::shared_ptr<Entity> ent = std::make_shared<Entity>(99);
	ent->AddComponent<TransformComponent>(glm::vec2{ -6, -6 });

	entList.AddEntity(ent);

	OrthographicCamera cam(-4, 4, -4, 4);

	EXPECT_EQ(0, entList.GetVisibleEntities(cam).size());
}