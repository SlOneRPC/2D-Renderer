#pragma once

#include <OpenGL/VertexLayout.h>

class VertexBuffer {
public:
	VertexBuffer(int size);
	VertexBuffer(void* data, int size);
	~VertexBuffer();

	void Bind();
	void Unbind();

	void SetData(float* data, int size);

	void SetLayout(VertexLayout& layout) { this->layout = layout; }
	VertexLayout& GetLayout() { return layout;  }
private:
	unsigned int bufferId;
	VertexLayout layout;
};