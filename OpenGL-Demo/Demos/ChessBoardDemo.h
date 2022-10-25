#pragma once
#include "QuadDemo.h"
#include "../Texture.h"

class ChessBoardDemo : QuadDemo
{
public:
	ChessBoardDemo();
	~ChessBoardDemo();

	void Init() override;
	void OnRender() override;
	void OnImguiRender() override;
	void Shutdown() override;

private:
	VertexBuffer* vertex;
	IndexBuffer* index;
	Shader* shader;
	Shader* textureShader;
	Texture* texture;
};