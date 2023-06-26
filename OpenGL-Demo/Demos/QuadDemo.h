#pragma once
#include "Demo.h"
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"
#include "../Shader.h"

class QuadDemo : Demo 
{
public:
	QuadDemo();
	~QuadDemo();

	void Init() override;
	void OnRender() override;
	void OnImguiRender() override;
	void Shutdown() override;

private:
	VertexBuffer* vertex;
	IndexBuffer* index;
	Shader* shader;
};