#include "VertexLayout.h"

VertexLayout::VertexLayout()
{
}

VertexLayout::VertexLayout(std::shared_ptr<VertexLayoutAtrrib>& attrib)
{
	AddAttrib(attrib);
}

VertexLayout::~VertexLayout()
{
}

void VertexLayout::Bind()
{
	for (std::shared_ptr<VertexLayoutAtrrib>& attrib : attribs)
	{
		attrib->Bind();
	}
}

VertexLayoutAtrrib::VertexLayoutAtrrib(int index, int size, GLenum type, bool normalised, int stride, void* pointer)
	: index(index),
	size(size),
	type(type),
	normalised(normalised),
	stride(stride), pointer(pointer)
{
}

void VertexLayoutAtrrib::Bind()
{
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, size, type, normalised, stride, pointer);
}
