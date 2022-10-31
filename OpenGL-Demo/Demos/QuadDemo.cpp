#include "QuadDemo.h"
#include "../CommonRender.h"

QuadDemo::QuadDemo()
{
	name = "Quad Demo";
}

QuadDemo::~QuadDemo()
{
	Shutdown();
}

void QuadDemo::Init()
{
	float vertexBuffer[] = {
		-0.5f, -0.5f, // 0
		0.5f, -0.5f,  // 1
		0.5f, 0.5f,   // 2
		-0.5f, 0.5f   // 3
	};

	vertex = new VertexBuffer(vertexBuffer, sizeof(vertexBuffer));

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	index = new IndexBuffer(indices, _countof(indices));
	shader = new Shader("shaders/vertex.shader", "shaders/fragment.shader");

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	vertex->Bind();
	index->Bind();
	shader->Bind();

	shader->SetUniformVec4("uColour", 1.f, 0.f, 0.f, 1.f);
}

void QuadDemo::OnRender()
{
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void QuadDemo::OnImguiRender()
{

}

void QuadDemo::Shutdown()
{
	delete vertex;
	delete index;
	delete shader;
}
