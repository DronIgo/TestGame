#pragma once
#include "Graphics/GL_include.h"
#include "ElementBuffer.h"
#include "VertexBuffer.h"

class VertexSpecification;

class VertexArray {
private:
	unsigned int ID;

	VertexBuffer vbo;
	unsigned int vbo_bindingIndex = 1;
	const VertexSpecification* specification;
	ElementBuffer ebo;
public:
	VertexArray();

	unsigned int getID() { return ID; };
	void bufferData(float* vertexData, unsigned int dataSize, unsigned int* indecies, unsigned int indeciesNum);
	void bufferData(float* vertexData, unsigned int dataSize);
	void setVertexSpecification(const VertexSpecification* specification);

	void bind();
	void unbind();
};