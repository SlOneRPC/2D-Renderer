#pragma once

class IndexBuffer {
public:
	IndexBuffer(const unsigned int* data, int count);
	~IndexBuffer();

	void Bind();
private:
	unsigned int bufferId;
};