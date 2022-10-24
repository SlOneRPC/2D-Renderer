#pragma once

class VertexBuffer {
public:
	VertexBuffer(int size);
	VertexBuffer(float* data, int size);
	~VertexBuffer();

	void Bind();
	void Unbind();

	void SetData(float* data, int size);
private:
	unsigned int bufferId;
};