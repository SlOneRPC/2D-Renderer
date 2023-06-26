#include "ChessBoardDemo.h"
#include "../CommonRender.h"

ChessBoardDemo::ChessBoardDemo()
{
}

ChessBoardDemo::~ChessBoardDemo()
{
	Shutdown();
}

void ChessBoardDemo::Init()
{
	unsigned int indices[] = {
				0, 1, 2,
				2, 3, 0
	};

	index = new IndexBuffer(indices, _countof(indices));
	shader = new Shader("shaders/vertex.shader", "shaders/fragment.shader");

	index->Bind();
	shader->Bind();
}

void ChessBoardDemo::OnRender()
{
	float size = 8;

	for (size_t x = 0; x < size; x++)
	{
		for (size_t y = 0; y < size; y++)
		{
			const float baseOffset = 1.f / (size / 2);

			float offset1x = (baseOffset * x) - 1;
			float offset2x = offset1x + (baseOffset);

			float offset1y = (baseOffset * y) - 1;
			float offset2y = offset1y + (baseOffset);

			float vertexBuffer[] = {
				offset1x, offset1y, // 0
				offset2x, offset1y,  // 1
				offset2x, offset2y,   // 2
				offset1x, offset2y   // 3
			};

			vertex = new VertexBuffer(vertexBuffer, sizeof(vertexBuffer));
			
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

			vertex->Bind();
			
			bool lightSquare = (x + y) % 2 == 0;
			shader->SetUniformVec4("uColour", lightSquare ? 0.90 : 0.49f, lightSquare ? 0.92f : 0.529f, lightSquare ? 0.937f : 0.588f, 1.0f);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

			delete vertex;
		}
	}
}

void ChessBoardDemo::OnImguiRender()
{

}

void ChessBoardDemo::Shutdown()
{
	delete index;
	delete shader;
}
