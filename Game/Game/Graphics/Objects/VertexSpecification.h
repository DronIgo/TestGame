#pragma once
#include <vector>
#include "Graphics/GL_include.h"

struct VertexElement {
	GLint size;
	GLenum type;
	GLboolean normalized;
};

class VertexSpecification {
private: 
	unsigned int byteStride;
	void calcStride();
public:
	VertexSpecification(const std::vector<VertexElement>& _elements);

	std::vector<VertexElement> elements;
	unsigned int getStride() { return byteStride; }
	unsigned int calcRelativeOffset(unsigned int numElements);
};