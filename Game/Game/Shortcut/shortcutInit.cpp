#include "shortcutInit.h"
#include "Graphics/GL_include.h"

#include "Graphics/Objects/VertexSpecification.h"
#include "Graphics/Objects/Shader.h"
#include "Graphics/Objects/Model.h"

#include "Utility/constants.h"

namespace {
	struct VertexXYZW {
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
	VertexXYZW triangle[] =
	{
		VertexXYZW{0.5, -0.5, 0.0, 1.0, 1.0, 0.0, 0.0},
		VertexXYZW{-0.5, -0.5, 0.0, 1.0, 0.0, 1.0, 0.0},
		VertexXYZW{0, 0.5, 0.0, 1.0, 0.0, 0.0, 1.0},
		VertexXYZW{0.5, -0.5, 0.0, 1.0, 1.0, 0.0, 0.0},
		VertexXYZW{-0.5, -0.5, 0.0, 1.0, 0.0, 1.0, 0.0},
		VertexXYZW{0, 0.5, 0.0, 1.0, 0.0, 0.0, 1.0}
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
	std::vector<VertexElement> elements =
	{
		VertexElement{4, GL_FLOAT, false, ElementType::XYZW },
		VertexElement{3, GL_FLOAT, false, ElementType::COLOR}
	};
	const VertexSpecification* spec = VertexSpecificationManager::instance().CreateVertexSpecification(elements);
	shaderTranslated = new Shader(shader_names::triangle_vs, shader_names::triangle_ps, spec);
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
