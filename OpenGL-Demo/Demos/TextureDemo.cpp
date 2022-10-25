#include "TextureDemo.h"
#include "../CommonRender.h"

TextureDemo::TextureDemo()
{
}

TextureDemo::~TextureDemo()
{
	Shutdown();
}

void TextureDemo::Init()
{
	float vertexBuffer[] = {
		-0.5f, -0.5f, 0.0f, 0.0f,  // 0
		0.5f, -0.5f, 1.0f, 0.0f,   // 1
		0.5f, 0.5f, 1.0f, 1.0f,   // 2
		-0.5f, 0.5f, 0.0f, 1.0f   // 3
	};

	vertex = new VertexBuffer(vertexBuffer, sizeof(vertexBuffer));

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	index = new IndexBuffer(indices, _countof(indices));
	shader = new Shader("shaders/vertex.shader", "shaders/textureFragment.shader");

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(sizeof(float) * 2));

	texture = new Texture("images/white-pieces/pawn.png");

	vertex->Bind();
	index->Bind();
	shader->Bind();
	texture->Bind(0);
}

void TextureDemo::OnRender()
{
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void TextureDemo::OnImguiRender()
{

}

void TextureDemo::Shutdown()
{
	delete vertex;
	delete index;
	delete shader;
}
