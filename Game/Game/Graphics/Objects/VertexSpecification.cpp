#include "VertexSpecification.h"
#include <iostream>
VertexSpecification::VertexSpecification(const std::vector<VertexElement>& _elements)
{
	elements.resize(_elements.size());
	std::copy(_elements.begin(), _elements.end(), elements.begin());
	calcStride();
}

unsigned int VertexSpecification::calcRelativeOffset(unsigned int numElements)
{
	if (numElements > elements.size()) {
		std::cout << __FUNCTION__ << ": numElements is higher than the elements vector size!" << std::endl;
		numElements = elements.size();
	}
	unsigned int offset = 0;
	for (int i = 0; i < numElements; ++i) {
		unsigned int typeSize = 0;
		switch (elements[i].type) {
		case GL_FLOAT:
			typeSize = sizeof(float);
			break;
		case GL_INT:
			typeSize = sizeof(int);
			break;
		default:
			std::cout << __FUNCTION__ << ": worng element format!" << std::endl;
		}
		offset += typeSize * elements[i].size;
	}
	return offset;
}

void VertexSpecification::calcStride() {
	byteStride = calcRelativeOffset(elements.size());
}
