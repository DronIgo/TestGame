#pragma once
#include <vector>
#include "Graphics/GL_include.h"
#include "Utility/Singleton.h"

enum class ElementType {
	XYZ,
	XYZW,
	NORMAL, 
	UV, 
	COLOR
};

struct VertexElement {
	GLint size;
	GLenum type;
	GLboolean normalized;
	ElementType elementType;
};

bool operator==(const VertexElement& elem1, const VertexElement& elem2);

class VertexSpecification {
private: 
	unsigned int byteStride;
	void calcStride();
public:
	VertexSpecification(const std::vector<VertexElement>& _elements);

	std::vector<VertexElement> elements;
	unsigned int getStride() const { return byteStride; }
	unsigned int calcRelativeOffset(unsigned int numElements) const;
	unsigned int getTotalSize() const;
};

bool operator== (const VertexSpecification& spec1, const VertexSpecification& spec2);

class VertexSpecificationManager : public Singleton<VertexSpecificationManager> {
private:
	std::vector<VertexSpecification> specifications;
public:
	VertexSpecificationManager() {}
	const VertexSpecification* CreateVertexSpecification(const std::vector<VertexElement>& _elements);
};