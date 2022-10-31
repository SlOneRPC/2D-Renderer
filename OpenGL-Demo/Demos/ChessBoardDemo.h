#pragma once
#include "QuadDemo.h"
#include "../Texture.h"

struct Vector2 {
	int x, y;

	bool operator==(const Vector2& other) const
	{
		return (x == other.x
			&& y == other.y);
	}
};

class ChessBoardDemo : Demo
{
public:
	ChessBoardDemo();
	~ChessBoardDemo();

	void Init() override;
	void OnRender() override;
	void OnImguiRender() override;
	void Shutdown() override;

private:
	void MovePiece(const std::string& name, Vector2& pos);

	VertexBuffer* vertex;
	IndexBuffer* index;
	Shader* shader;
	Shader* textureShader;
	Texture* texture;
};