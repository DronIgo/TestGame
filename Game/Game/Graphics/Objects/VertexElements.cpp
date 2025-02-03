#include "VertexElements.h"

VertexElements::VertexElements(int _maxSize)
{

}

void VertexElements::bufferData(unsigned int* data, unsigned int size)
{
	glCreateBuffers(1, &ID);
	glNamedBufferData(ID, size, data, GL_STATIC_DRAW);
}

void VertexElements::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}
