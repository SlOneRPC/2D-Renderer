#include "QuadTree.h"
#include "Core/Logging.h"
#include <format>

// TEMP
#include "Renderer/Renderer2D.h"
#include "imgui.h"

int MaxEntitiesPerNode = 5;
int MinEntitiesPerLinkNode = MaxEntitiesPerNode / 2;
float MinNodeSize = 0.05f;

void QuadTree::AddEntity(Entity* entity)
{
	if (!entity->HasComponent<TransformComponent>())
	{
		LOG_ERROR("Entity does not have a transform component!");
		assert(0);
		return;
	}

	TransformComponent* transform = entity->GetComponent<TransformComponent>();

	glm::vec2 offset = glm::vec2(transform->scale.x, transform->scale.y) / 2.f;

	BoundingBox box(transform->translation - offset, transform->translation + offset);
	trackers.previousBox.emplace(entity->id, box);

	rootNode->AddEntity(entity, box);
}

void QuadTree::RemoveEntity(Entity* entity)
{
	rootNode->RemoveEntity(entity, trackers.previousBox.at(entity->id));
}

void QuadTree::MoveEntity(Entity* entity)
{
	TransformComponent* transform = entity->GetComponent<TransformComponent>();
	glm::vec2 offset = glm::vec2(transform->scale.x, transform->scale.y) / 2.f;
	BoundingBox newBox(transform->translation - offset, transform->translation + offset);

	rootNode->UpdateEntityPosition(entity, newBox, trackers.previousBox.at(entity->id));
	trackers.previousBox[entity->id] = newBox;
}

std::vector<Entity*> QuadTree::GetEntities()
{
	std::vector<Entity*> ents;
	rootNode->SelectAll(ents);
	return ents;
}

std::vector<Entity*> QuadTree::GetEntities(const glm::vec2& min, const glm::vec2& max)
{
	std::vector<Entity*> ents;
	BoundingBox box(min, max);
	rootNode->SelectAll(box, ents);
	return ents;
}

std::vector<Entity*> QuadTree::GetCollidingEntities(Entity* other)
{
	std::vector<Entity*> ents;
	BoundingBox box = trackers.previousBox[other->id];
	rootNode->SelectAll(box, ents);

	std::vector<Entity*> finalEnts;

	for (Entity* ent : ents) 
	{
		if (box.contains(trackers.previousBox[ent->id])) 
		{
			finalEnts.push_back(ent);
		}
	}

	return finalEnts;
}

void QuadTree::Draw()
{
#ifdef DEBUG
	// Tree specific settings
	ImGui::PushItemWidth(150);
	ImGui::DragInt("Max entities per node", &MaxEntitiesPerNode, 1.0f, 1, 100);
	ImGui::DragInt("Min entities per link node", &MinEntitiesPerLinkNode, 1.0f, 1, 100);
	ImGui::DragFloat("Min node size", &MinNodeSize, 1.0f, 0.01, 10);
	ImGui::PopItemWidth();

	ImGui::Separator();

#endif

	Colour col;
	int id = 0;
	rootNode->Draw(col, id);
}

void QuadTree::Recreate(float newSize)
{
	delete rootNode;
	trackers.previousBox.clear();
	rootNode = new Node(&trackers, nullptr, origin, newSize > 0.f ? newSize : size);
}

QuadTree::QuadTree(glm::vec2 origin, float size)
	: origin(origin), size(size)
{
	rootNode = new Node(&trackers, nullptr, origin, size);
}

QuadTree::~QuadTree()
{
	delete rootNode;
}

Node::Node(Trackers* trackers, Node* parent, glm::vec2 centrePoint, float size)
	: trackers(trackers), parent(parent), centrePoint(centrePoint), size(size), leafNode(true)
{
	float halfSize = size / 2.0f;

	boundingBox = BoundingBox {
		glm::vec2 { centrePoint.x - halfSize, centrePoint.y - halfSize },
		glm::vec2 { centrePoint.x + halfSize, centrePoint.y + halfSize }
	};

	if (!parent)
		SplitNode();
}

void Node::AddEntity(Entity* entity, BoundingBox& area)
{
	if (ContainsEntity(entity))
		return;

	if (leafNode) 
	{
		if (size / 2.0f < MinNodeSize || entities.size() < MaxEntitiesPerNode)
		{
			//std::string message = "Assigned entity: id-> " + std::to_string(entity->id) + " posx-> " + std::to_string(entity->GetComponent<TransformComponent>()->translation.x) + " posy-> " + std::to_string(entity->GetComponent<TransformComponent>()->translation.y);
			//LOG_INFO(message);
			//LOG_INFO(std::format("Entity Area min ({}, {}) max ({}, {})", area.Min.x, area.Min.y, area.Max.x, area.Max.y));
			//LOG_INFO(std::format("Area min ({}, {}) max ({}, {}) \n", boundingBox.Min.x, boundingBox.Min.y, boundingBox.Max.x, boundingBox.Max.y));

			entities.push_back(entity);
		}
		else 
		{
			SplitNode();

			for (int idx = 0; idx < entities.size(); idx++)
			{
				Entity* otherEntity = entities[idx];

				AssignEntity(otherEntity, trackers->previousBox[otherEntity->id]);
			}

			AssignEntity(entity, area);
		}
	}
	else 
	{
		AssignEntity(entity, area);
	}
}

void Node::RemoveEntity(Entity* entity, BoundingBox& area)
{
	if (leafNode) 
	{
		entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
	}
	else 
	{
		for (int idx = 0; idx < children.size(); idx++)
		{
			children[idx].RemoveEntity(entity, area);
		}

		if (parent) 
		{
			int storedEntities = GetEntityCount();

			if (storedEntities < MinEntitiesPerLinkNode)
				CollapseNode();
		}
	}
}

Node Node::CreateChildNode(glm::vec2 centrePoint, float size)
{
	return { trackers, this, centrePoint, size };
}

void Node::SplitNode()
{
	float halfSize = size / 2.0f;
	float offset = size / 4.0f;

	#define Add_Child(child) children.push_back(child)

	Add_Child(CreateChildNode(centrePoint + glm::vec2(offset, offset), halfSize));
	Add_Child(CreateChildNode(centrePoint + glm::vec2(-offset, offset), halfSize));
	Add_Child(CreateChildNode(centrePoint + glm::vec2(offset, -offset), halfSize));
	Add_Child(CreateChildNode(centrePoint + glm::vec2(-offset, -offset), halfSize));

	// Tidy up current node
	if (entities.size() > 0) 
	{
		for (int childIdx = 0; childIdx < 4; childIdx++)
		{
			for (Entity* ent : entities) 
			{
				children[childIdx].AssignEntity(ent, trackers->previousBox[ent->id]);
			}
		}
		entities.clear();
	}

	leafNode = false;
}

void Node::CollapseNode()
{
	for (int childIdx = 0; childIdx < 4; childIdx++)
	{
		Node* childNode = &children[childIdx];

		if (!childNode->leafNode) 
		{
			childNode->CollapseNode();
		}

		for (int entityIdx = 0; entityIdx < childNode->entities.size(); entityIdx++)
		{
			Entity* entity = childNode->entities[entityIdx];
			entities.push_back(entity);
		}
	}

	children.clear();
	leafNode = true;
}

int Node::GetEntityCount()
{
	if (leafNode)
		return entities.size();
	else 
	{
		int count = 0;
		for (int idx = 0; idx < children.size(); idx++)
		{
			count += children[idx].GetEntityCount();
		}
		return count;
	}
}

void Node::Draw(Colour& col, int& id)
{
	if (leafNode) 
	{
		const Colour white{ 1.0f, 1.0f, 1.0f, 1.0f };
		g_Renderer->DrawOutlineQuad(boundingBox.Min + ((boundingBox.Max - boundingBox.Min) / 2.f), { boundingBox.area.width, boundingBox.area.height }, white, 0.05f);
#ifdef DEBUG
		ImGui::PushID(id);
		ImGui::Text((std::format("Node {} details:", std::to_string(id)).c_str()));
		ImGui::Text(("Entities=" + std::to_string(entities.size())).c_str());
		ImGui::Text((std::format("Min bounds x={},y={}", boundingBox.Min.x, boundingBox.Min.y)).c_str());
		ImGui::Text((std::format("Max bounds x={},y={}", boundingBox.Max.x, boundingBox.Max.y)).c_str());
		ImGui::PopID();
		ImGui::Separator();
		id++;
#endif
	}
	else 
	{
		const Colour childColours[] = {
			{ 0.0f, 1.0f, 1.0f, 0.5f },
			{ 0.0f, 1.0f, 0.0f, 0.5f },
			{ 0.0f, 0.0f, 1.0f, 0.5f },
			{ 1.0f, 0.0f, 1.0f, 0.5f },
		};

		for (int idx = 0; idx < children.size(); idx++)
		{
			Colour col = childColours[idx];
			children[idx].Draw(col, id);
		}
	}
}

void Node::AssignEntity(Entity* entity, BoundingBox& area)
{
	if (boundingBox.contains(area)) 
	{
		if (leafNode) 
		{
			AddEntity(entity, area);
		}
		else 
		{
			for (int idx = 0; idx < children.size(); idx++)
			{
				children[idx].AssignEntity(entity, area);
			}
		}
	}
}

bool Node::UpdateEntityPosition(Entity* entity, BoundingBox& newArea, BoundingBox& oldArea)
{
	if (leafNode) 
	{
		if (!boundingBox.contains(newArea)) 
		{
			RemoveEntity(entity, oldArea);
			return false;
		}

		return true;
	}
	else 
	{
		bool entityFound = false, entityAdded = false;

		for (int idx = 0; idx < children.size(); idx++)
		{
			Node* child = &children[idx];

			if (child->boundingBox.contains(oldArea)) 
			{
				bool found = children[idx].UpdateEntityPosition(entity, newArea, oldArea);
				if (found) entityFound = true;
			}
			else if (child->boundingBox.contains(newArea))
			{
				child->AssignEntity(entity, newArea);
				entityAdded = true;
			}
		}

		if (!entityFound && !entityAdded)
		{
			if (parent)
			{
				if (GetEntityCount() <= MaxEntitiesPerNode)
				{
					CollapseNode();
				}
			}
		}

		return entityFound;
	}
}

bool Node::ContainsEntity(Entity* entity)
{
	for (Entity* ent : entities) 
	{
		if (entity == ent) return true;
	}
	return false;
}

void Node::SelectAll(std::vector<Entity*>& ents)
{
	if (leafNode) 
	{
		for (int idx = 0; idx < entities.size(); idx++) 
		{
			Entity* ent = entities[idx];
				
			if (std::find(ents.begin(), ents.end(), ent) == ents.end())
				ents.push_back(ent);
		}
	}
	else 
	{
		for (int idx = 0; idx < children.size(); idx++)
		{
			children[idx].SelectAll(ents);
		}
	}
}

void Node::SelectAll(BoundingBox& area, std::vector<Entity*>& ents)
{
	if (boundingBox.contains(area))
	{
		if (leafNode)
		{
			for (int idx = 0; idx < entities.size(); idx++)
			{
				Entity* ent = entities[idx];

				if (std::find(ents.begin(), ents.end(), ent) == ents.end())
					ents.push_back(ent);
			}
		}
		else
		{
			for (int idx = 0; idx < children.size(); idx++)
			{
				children[idx].SelectAll(area, ents);
			}
		}
	}
}