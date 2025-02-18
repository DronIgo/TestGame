#include "VertexArray.h"
#include "VertexSpecification.h"

VertexArray::VertexArray()
{

}

void VertexArray::bufferData(float* vertexData, unsigned int dataSize, unsigned int* indecies, unsigned int indeciesSize)
{
	glCreateVertexArrays(1, &ID);
	vbo.bufferData(vertexData, dataSize);
	ebo.bufferData(indecies, indeciesSize);
	glVertexArrayElementBuffer(ID, ebo.getID());
}

void VertexArray::bufferData(float* vertexData, unsigned int dataSize)
{
	glCreateVertexArrays(1, &ID);
	vbo.bufferData(vertexData, dataSize);
}

void VertexArray::setVertexSpecification(const VertexSpecification* _specification)
{
	specification = _specification;
	glVertexArrayVertexBuffer(ID, vbo_bindingIndex, vbo.getID(), 0, specification->getStride());

	int attribIndex = 0;
	for (auto& element : specification->elements) {
		glEnableVertexArrayAttrib(ID, attribIndex);
		glVertexArrayAttribFormat(ID, attribIndex, element.size, element.type, element.normalized, 
			specification->calcRelativeOffset(attribIndex));
		glVertexArrayAttribBinding(ID, attribIndex, vbo_bindingIndex);

		attribIndex++;
	}
}

void VertexArray::bind()
{
	glBindVertexArray(ID);
}

void VertexArray::unbind()
{
	glBindVertexArray(0);
}
