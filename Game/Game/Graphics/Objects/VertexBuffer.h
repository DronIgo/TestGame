#pragma once
#include "Graphics/GL_include.h"

class VertexBuffer {
private:
	unsigned int ID;
	unsigned int offset = 0;
	//For now not used
	unsigned int maxSize = 0;
public:
	VertexBuffer(int _maxSize = 0);

	unsigned int getID() { return ID; };
	void bufferData(float* data, int size);
	void bind();

	~VertexBuffer();
};