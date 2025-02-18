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
	Shader* shaderChair;

	VertexArray triangleVAO;
	VertexBuffer vbo;

	Model* modelChair;
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
		VertexElement{4, GL_FLOAT, false, ElementType::XYZW},
		VertexElement{3, GL_FLOAT, false, ElementType::COLOR}
	};
	VertexSpecification spec(elements);

	triangleVAO.bufferData((float*)triangle, sizeof(triangle));
	triangleVAO.setVertexSpecification(&spec);


	modelChair = new Model(std::filesystem::path("Resources\\Models\\old_wooden_chair\\old_wooden_chair.fbx"));
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

	shaderChair = new Shader(shader_names::chair_vs, shader_names::chair_ps, NULL);
}

void render()
{
	glClearColor(0.2, 0.0, 0.2, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(0.01, 0.01, 0.01));
	glm::mat4 view = glm::lookAt(glm::vec3(0, 0, -10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 proj = glm::perspective(glm::radians(60.0f), (float)800 / (float)600, 0.1f, 100.0f);
	shaderChair->setMat4f("model", model);
	shaderChair->setMat4f("view", view);
	shaderChair->setMat4f("proj", proj);
	//shaderTranslated->use();
	//triangleVAO.bind();
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	//triangleVAO.unbind();
	shaderChair->use();
	modelChair->Draw(*shaderChair);
}
