#pragma once

#include <OpenGL/VertexBuffer.h>
#include <OpenGL/IndexBuffer.h>

class VertexArray {
public:
	VertexArray();
	VertexArray(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer);
	~VertexArray();

	void Bind();
	void UnBind();

	void AddVertexArray(const std::shared_ptr<VertexBuffer>& vertexBuffer);
	void AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);
private:
	std::vector<std::shared_ptr<VertexBuffer>> vBuffers;
	std::vector<std::shared_ptr<IndexBuffer>> IBuffers;
	unsigned int id;
};