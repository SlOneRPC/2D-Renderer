#include "pch.h"
#include "Scene/Entity.h"

TEST(EntityTests, EnsureEntityIdIsStored) {

	Entity ent(1);
	EXPECT_EQ(1, ent.id);
	Entity ent2(2);
	EXPECT_EQ(2, ent2.id);
}

TEST(EntityTests, EnsureComponentCanBeAdded) {
	
	Entity ent(1);
	ent.AddComponent<TransformComponent>(glm::vec2{0, 0});
	EXPECT_TRUE(ent.HasComponent<TransformComponent>());
}

TEST(EntityTests, EnsureTransformComponentStoresPositon) {

	Entity ent(1);
	ent.AddComponent<TransformComponent>(glm::vec2{ 1, 0 });

	EXPECT_TRUE(ent.HasComponent<TransformComponent>());
	EXPECT_EQ(1, ent.GetComponent<TransformComponent>()->translation.x);
}

TEST(EntityTests, EnsureQuadComponentStoresColour) {

	Entity ent(1);
	Colour col{ 1, 1, 1, 1 };
	ent.AddComponent<QuadComponent>(col);

	EXPECT_TRUE(ent.HasComponent<QuadComponent>());
	EXPECT_EQ(1, ent.GetComponent<QuadComponent>()->colour.r);
}

class TestEntity : public Entity {
public:
	TestEntity(int id) : Entity(id) {}

	virtual void OnUpdate(TimeStep ts)
	{
		updateCalled = true;
	}

	virtual void OnCreate() 
	{
		onCreateCalled = true;
	}

	bool onCreateCalled = false;
	bool updateCalled = false;
};

TEST(EntityTests, EnsureUpdateIsCalledOnOverridedEntity) 
{

	std::shared_ptr<Entity> ent = std::make_shared<TestEntity>(1);

	TimeStep ts;

	ent->OnUpdate(ts);

	EXPECT_TRUE(dynamic_cast<TestEntity*>(ent.get())->updateCalled);
}

TEST(EntityTests, EnsureOnCreateIsCalledOnOverridedEntity)
{
	std::shared_ptr<Entity> ent = std::make_shared<TestEntity>(1);

	ent->OnCreate();

	EXPECT_TRUE(dynamic_cast<TestEntity*>(ent.get())->onCreateCalled);
}