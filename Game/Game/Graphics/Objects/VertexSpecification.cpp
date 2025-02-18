#include "VertexSpecification.h"
#include <iostream>
#include <algorithm>

VertexSpecification::VertexSpecification(const std::vector<VertexElement>& _elements)
{
	elements.resize(_elements.size());
	std::copy(_elements.begin(), _elements.end(), elements.begin());
	calcStride();
}

unsigned int VertexSpecification::calcRelativeOffset(unsigned int numElements) const
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

unsigned int VertexSpecification::getTotalSize() const
{
	unsigned int totalSize = 0;
	for (auto& elem : elements)
		totalSize += elem.size;
	return totalSize;
}

void VertexSpecification::calcStride() {
	byteStride = calcRelativeOffset(elements.size());
}

bool operator==(const VertexElement& elem1, const VertexElement& elem2)
{
	return elem1.type == elem2.type && elem1.size == elem2.size && elem1.normalized == elem2.normalized;
}

bool operator==(const VertexSpecification& spec1, const VertexSpecification& spec2)
{
	if (spec1.elements.size() != spec2.elements.size())
		return false;
	for (int i = 0; i < spec1.elements.size(); ++i) {
		if (spec1.elements[i] != spec2.elements[i]) {
			return false;
		}
	}
	return true;
}

const VertexSpecification* VertexSpecificationManager::CreateVertexSpecification(const std::vector<VertexElement>& _elements)
{
	for (auto& spec : specifications) {
		if (spec.elements == _elements)
			return &spec;
	}

	specifications.push_back(VertexSpecification(_elements));
	return &specifications[specifications.size() - 1];
}
