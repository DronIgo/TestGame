#pragma once
#include "Graphics/GL_include.h"

class VertexElements {
private:
	unsigned int ID;
	unsigned int offset = 0;
	//For now not used
	unsigned int maxSize = 0;
public:
	VertexElements(int _maxSize = 0);
	unsigned int getID() { return ID; };
	void bufferData(unsigned int* data, unsigned int size);
	void bind();
};