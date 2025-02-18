#include "ElementBuffer.h"

ElementBuffer::ElementBuffer(int _maxSize)
{

}

void ElementBuffer::bufferData(unsigned int* data, unsigned int size)
{
	glCreateBuffers(1, &ID);
	glNamedBufferData(ID, size, data, GL_STATIC_DRAW);
}

void ElementBuffer::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}
