#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(int _maxSize) : maxSize(_maxSize)
{

}

void VertexBuffer::bufferData(float* data, int size)
{
	glCreateBuffers(1, &ID);
	glNamedBufferData(ID, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &ID);
}
