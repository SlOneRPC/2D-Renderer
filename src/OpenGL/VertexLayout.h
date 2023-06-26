#pragma once
#include <OpenGL/CommonRender.h>
#include <vector>
#include <memory>

class VertexLayoutAtrrib {
public:
	VertexLayoutAtrrib(int index, int size, GLenum type, bool normalised, int stride, void* pointer);
	void Bind();

	int index;
	int size;
	GLenum type;
	bool normalised;
	int stride;
	const void* pointer;
};

class VertexLayout {
public:
	VertexLayout();
	VertexLayout(std::shared_ptr<VertexLayoutAtrrib>& attrib);
	~VertexLayout();

	void AddAttrib(std::shared_ptr<VertexLayoutAtrrib> attrib) { attribs.push_back(attrib); };
	void Bind();
	bool IsSet() { return attribs.size() > 0; }
private:
	std::vector<std::shared_ptr<VertexLayoutAtrrib>> attribs;
};