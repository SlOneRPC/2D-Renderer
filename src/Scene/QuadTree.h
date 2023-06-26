#pragma once
#include "glm/vec2.hpp"
#include <vector>
#include "Entity.h"

#include "OpenGL/OrthographicCamera.h"
#include <map>

struct BoundingArea { float width, height; };

struct BoundingBox { 
	glm::vec2 Min, Max;
	BoundingArea area;

	inline BoundingBox() {};

	inline BoundingBox(glm::vec2 minpos, glm::vec2 maxpos)
		: Min(minpos), Max(maxpos)
	{
		area.width = abs(this->Max.x - this->Min.x);
		area.height = abs(this->Max.y - this->Min.y);
	}

	inline bool contains(BoundingBox& box) {
		return box.Min.x < this->Max.x && box.Max.x > this->Min.x &&
			box.Max.y > this->Min.y && box.Min.y < this->Max.y;


	/*	return (abs(box.Min.x - this->Min.x) * 2 < (this->area.width + box.area.width) &&
			(abs(box.Min.y - this->Min.y) * 2 < (this->area.height + box.area.height)));*/
	}
};

struct Trackers {
	std::map<int, BoundingBox> previousBox;
};

class Node {
public:
	Node(Trackers* trackers, Node* parent, glm::vec2 centrePoint, float size);

	// Entity
	void AddEntity(Entity* entity, BoundingBox& area);
	void RemoveEntity(Entity* entity, BoundingBox& area);
	bool UpdateEntityPosition(Entity* entity, BoundingBox& newArea, BoundingBox& oldArea);

	// Selecting
	void SelectAll(std::vector<Entity*>& ents);
	void SelectAll(BoundingBox& area, std::vector<Entity*>& ents);

	// Debug
	void Draw(Colour& col, int& id);

private:
	Node CreateChildNode(glm::vec2 centrePoint, float size);

	// Entity
	void AssignEntity(Entity* entity, BoundingBox& area);
	bool ContainsEntity(Entity* entity);

	// New nodes
	void SplitNode();
	void CollapseNode();

	int GetEntityCount();
	
	glm::vec2 centrePoint;
	float size;

	Node* parent;
	std::vector<Node> children;
	std::vector<Entity*> entities;

	BoundingBox boundingBox;
	Trackers* trackers;
	bool leafNode;
};

class QuadTree {
public:
	QuadTree(glm::vec2 origin, float size);
	~QuadTree();

	void AddEntity(Entity* entity);
	void RemoveEntity(Entity* entity);
	void MoveEntity(Entity* entity);

	std::vector<Entity*> GetEntities();
	std::vector<Entity*> GetEntities(const glm::vec2& min, const glm::vec2& max);

	void Draw();
	void Recreate();


	// Determine Intersection
	// Determine Contacts
private:
	glm::vec2 origin;
	float size;
	Node* rootNode;
	Trackers trackers;
};