#include "pch.h"
#include "Scene/QuadTree.h"

TEST(QuadTreeTests, EnsureQuadTreeCanBeCreated) {

	QuadTree tree({ 0,0 }, 8.f);

	EXPECT_EQ(0, tree.GetEntities().size());
}

TEST(QuadTreeTests, EnsureQuadTreeCanAddEntity) {

	QuadTree tree({ 0,0 }, 8.f);

	Entity ent(1);
	ent.AddComponent<TransformComponent>(glm::vec2{ 0,0 });

	tree.AddEntity(&ent);

	EXPECT_EQ(1, tree.GetEntities().size());
	EXPECT_EQ(&ent, tree.GetEntities()[0]);
}

TEST(QuadTreeTests, EnsureQuadTreeCanRemoveEntity) {

	QuadTree tree({ 0,0 }, 8.f);

	Entity ent(1);
	ent.AddComponent<TransformComponent>(glm::vec2{ 0,0 });

	tree.AddEntity(&ent);

	EXPECT_EQ(1, tree.GetEntities().size());
	EXPECT_EQ(&ent, tree.GetEntities()[0]);

	tree.RemoveEntity(&ent);

	EXPECT_EQ(0, tree.GetEntities().size());
}

TEST(QuadTreeTests, EnsureQuadTreeCanMoveEntity) {

	QuadTree tree({ 0,0 }, 8.f);

	Entity ent(1);
	ent.AddComponent<TransformComponent>(glm::vec2{ 0,0 });

	tree.AddEntity(&ent);

	ent.GetComponent<TransformComponent>()->translation = glm::vec2{ 3, 3 };

	tree.MoveEntity(&ent);

	EXPECT_EQ(1, tree.GetEntities().size());
	EXPECT_EQ(&ent, tree.GetEntities()[0]);
	EXPECT_EQ(3, tree.GetEntities()[0]->GetComponent<TransformComponent>()->translation.x);
}

TEST(QuadTreeTests, EnsureQuadTreeCanGetEntityInCorrectArea) {

	QuadTree tree({ 0,0 }, 8.f);

	Entity ent(1);
	ent.AddComponent<TransformComponent>(glm::vec2{ 0,0 });

	tree.AddEntity(&ent);

	auto entities = tree.GetEntities(glm::vec2{-1,-1}, glm::vec2{ 0, 0 });

	EXPECT_EQ(1, entities.size());
	EXPECT_EQ(&ent, entities[0]);

	ent.GetComponent<TransformComponent>()->translation = glm::vec2{ 3, 3 };
	tree.MoveEntity(&ent);

	auto entitiesUpdated = tree.GetEntities(glm::vec2{ -1,-1 }, glm::vec2{ 0, 0 });

	EXPECT_EQ(0, entitiesUpdated.size());
}

TEST(QuadTreeTests, EnsureQuadTreeCanBeRecreated) {

	QuadTree tree({ 0,0 }, 8.f);

	Entity ent(1);
	ent.AddComponent<TransformComponent>(glm::vec2{ 0,0 });

	tree.AddEntity(&ent);

	tree.Recreate();

	EXPECT_EQ(0, tree.GetEntities().size());
}