#include "VertexArray.h"

VertexArray::VertexArray()
{
	glCreateVertexArrays(1, &id);
}

VertexArray::VertexArray(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer)
{
	glCreateVertexArrays(1, &id);
	AddVertexArray(vertexBuffer);
	AddIndexBuffer(indexBuffer);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &id);
}

void VertexArray::Bind()
{
	glBindVertexArray(id);
}

void VertexArray::UnBind()
{
	glBindVertexArray(0);
}

void VertexArray::AddVertexArray(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
	Bind();
	vertexBuffer->Bind();

	if (vertexBuffer->GetLayout().IsSet()) 
	{
		vertexBuffer->GetLayout().Bind();
	}

	vBuffers.push_back(vertexBuffer); // Store ref so it isn't deleted by calling
}

void VertexArray::AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
	Bind();
	indexBuffer->Bind();

	IBuffers.push_back(indexBuffer);
}
