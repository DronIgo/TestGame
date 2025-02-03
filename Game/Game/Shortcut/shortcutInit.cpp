#include "shortcutInit.h"
#include "Graphics/GL_include.h"

#include "Graphics/Objects/VertexSpecification.h"
#include "Graphics/Objects/Shader.h"
namespace {
	struct Vertex {
		//position
		float x, y, z, w;
		//color
		float r, g, b;
	};

	Shader* shaderTranslated;

	VertexArray triangleVAO;
	VertexBuffer vbo;
}
void initGLStates()
{
	//glEnable(GL_DEPTH_TEST);
}

unsigned int vaoID;
unsigned int vboID;

void initGraphics()
{
	Vertex triangle[] =
	{
		Vertex{0.5, -0.5, 0.0, 1.0, 1.0, 0.0, 0.0},
		Vertex{-0.5, -0.5, 0.0, 1.0, 0.0, 1.0, 0.0},
		Vertex{0, 0.5, 0.0, 1.0, 0.0, 0.0, 1.0},
		Vertex{0.5, -0.5, 0.0, 1.0, 1.0, 0.0, 0.0},
		Vertex{-0.5, -0.5, 0.0, 1.0, 0.0, 1.0, 0.0},
		Vertex{0, 0.5, 0.0, 1.0, 0.0, 0.0, 1.0}
	};
	std::vector<VertexElement> elements =
	{
		VertexElement{4, GL_FLOAT, false},
		VertexElement{3, GL_FLOAT, false}
	};
	VertexSpecification spec(elements);

	triangleVAO.bufferData((float*)triangle, sizeof(triangle));
	triangleVAO.setVertexSpecification(&spec);
}

void initShaders()
{
	shaderTranslated = new Shader("Graphics/Shaders/vertex_shaders/translated_color.vs",
								  "Graphics/Shaders/pixel_shaders/color.ps");
}

void render()
{
	glClearColor(0.2, 0.0, 0.2, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	shaderTranslated->use();
	triangleVAO.bind();
	glDrawArrays(GL_TRIANGLES, 0, 3);
	triangleVAO.unbind();
}
