// Tuto1.cpp : définit le point d'entrée pour l'application console.
//

#include <stdio.h>
#include <stdlib.h>

#include <string>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <glm\gtc\matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../GoodCore/Core/GLSLPipeline.h"
#include "../GoodCore/Core/LoaderObj.h"
#include "../GoodCore/Core/Mesh.h"
#include "../GoodCore/Core/FrameBufferObject.h"
#include "../GoodCore/Core/Camera.h"

static void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
void computeMotion(GLFWwindow* window, int key, int action);

using namespace Good;

ViewportPtr gViewport = nullptr;
CameraPtr gCamera = nullptr;
int whatRender = 0;
bool showNormal = false;

void renderToTexture(MaterialPtr material, FrameBufferObjectPtr fbo);

void renderToTexture(MaterialPtr material, FrameBufferObjectPtr fbo)
{
	material->use();

	glDisable(GL_DEPTH_TEST);
	GLuint quad_VertexArrayID;
	glGenVertexArrays(1, &quad_VertexArrayID);
	glBindVertexArray(quad_VertexArrayID);

	static const GLfloat g_quad_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
	};

	GLuint quad_vertexbuffer;
	glGenBuffers(1, &quad_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);

	// Create and compile our GLSL program from the shaders
	ShaderProgramPtr fragmentShader = material->fragmentShader();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, 1024, 768);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (whatRender)
	{
	case 0:
		glBindTexture(GL_TEXTURE_2D, fbo->colorBuffer());
		break;
	case 1:
		glBindTexture(GL_TEXTURE_2D, fbo->normalBuffer());
		break;
	case 2:
		glBindTexture(GL_TEXTURE_2D, fbo->depthBuffer());
		break;
	}

	GLint texLoc = glGetUniformLocation(fragmentShader->id(), "tex0");
	GLint linearise = glGetUniformLocation(fragmentShader->id(), "linearize");
	glProgramUniform1i(fragmentShader->id(), texLoc, 0);
	glProgramUniform1i(fragmentShader->id(), linearise, whatRender);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
}

int main(int argc, char* argv[])
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1024, 768, "Tuto OpenGL", NULL, NULL);

	// Open a window and create its OpenGL context
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = true;
	GLenum err = glewInit();

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	printf("%s\n", glGetString(GL_VERSION));

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	static const GLfloat cubeBufferData[] = {
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f
	};

	GLSLPipelinePtr pipeline(new GLSLPipeline);

	ShaderProgramPtr passthroughVS(new ShaderProgram(pipeline, "../Shaders/Passthrough.vert", GL_VERTEX_SHADER, "passthroughVS"));
	ShaderProgramPtr transformVS(new ShaderProgram(pipeline, "../Shaders/SimpleTransform.vert", GL_VERTEX_SHADER, "transforVS"));

	ShaderProgramPtr colorFS(new ShaderProgram(pipeline, "../Shaders/ColorFragmentShader.frag", GL_FRAGMENT_SHADER, "colorFragment"));
	ShaderProgramPtr simpleFS(new ShaderProgram(pipeline, "../Shaders/SimpleFragmentShader.frag", GL_FRAGMENT_SHADER, "simpleFS"));
	ShaderProgramPtr textureFS(new ShaderProgram(pipeline, "../Shaders/SimpleTexture.frag", GL_FRAGMENT_SHADER, "textureFS"));

	ShaderProgramPtr passthroughGS(new ShaderProgram(pipeline, "../Shaders/Passthrough.geom", GL_GEOMETRY_SHADER, "passthroughGS"));
	ShaderProgramPtr normalGS(new ShaderProgram(pipeline, "../Shaders/NormalViewer.geom", GL_GEOMETRY_SHADER, "normalGS"));
	
	if (!pipeline->isValid())
		return -5;

	MaterialPtr material(new Material(transformVS, colorFS));
	MaterialPtr materialRTT(new Material(passthroughVS, textureFS));

	std::vector<MeshPtr> MeshList;
	int nbMesh = 0;

	ILoader* loader = new LoaderObj;
	MeshPtr loadedMesh = loader->load("X:\\DevGit\\Good-Engine\\Assets\\Objects\\sphere.obj");
	loadedMesh->setPosition(glm::vec3(0.0, 0.0, -1.0));
	loadedMesh->setMaterial(material);
	loadedMesh->init();
	MeshList.push_back(loadedMesh);	

	for (int idMesh = 0; idMesh < nbMesh; ++idMesh)
	{
		MeshPtr mesh(new Mesh(NameTools::nameGenerator(), nullptr));

		for (int idx = 0; idx < sizeof(cubeBufferData) / 4; idx += 3)
		{
			Vertex vertex;

			vertex.position = glm::vec3(cubeBufferData[idx], cubeBufferData[idx + 1], cubeBufferData[idx + 2]);
			mesh->addVertex(vertex);
		}

		float posFactor = 0.1f * (float)idMesh;
		mesh->setPosition(glm::vec3(posFactor));
		mesh->setScale(glm::vec3(0.5, 1.0, 0.75));
		mesh->setMaterial(material);
		mesh->init();		

		MeshList.push_back(mesh);
	}

	gViewport = ViewportPtr(new Viewport(0, 0, 1024, 768));
	gCamera = CameraPtr(new Camera(gViewport));

	FrameBufferObjectPtr fbo(new FrameBufferObject(gViewport->width(), gViewport->height()));

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	struct WorldTransform
	{
		glm::mat4 modelMatrix;
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
		glm::mat4 normalMatrix;
	};
	
	GLuint bufferID;
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_UNIFORM_BUFFER, bufferID);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(WorldTransform), NULL, GL_DYNAMIC_DRAW);

	float angle = .01;
	float xFactor = 0.0;

	do{
		fbo->bind();
		if (showNormal)
			normalGS->use();
		else
			passthroughGS->use();

		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		for (int meshIndex = 0; meshIndex <= nbMesh; ++meshIndex)
		{
			MeshList[meshIndex]->yaw(angle);
			transformVS->use();
			glBindBufferBase(GL_UNIFORM_BUFFER, 0, bufferID);
			WorldTransform *transform = (WorldTransform*)glMapBufferRange(GL_UNIFORM_BUFFER, 0, sizeof(WorldTransform), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
				
			transform->modelMatrix = MeshList[meshIndex]->localMatrix();
			transform->viewMatrix = gCamera->viewMatrix();
			transform->projectionMatrix = gCamera->projectionMatrix();
			glm::mat4 modelView = gCamera->viewMatrix() * MeshList[meshIndex]->localMatrix();
			transform->normalMatrix = glm::transpose(glm::inverse(modelView));

			glUnmapBuffer(GL_UNIFORM_BUFFER);
			glm::mat4 localToWorldMatrix = MeshList[meshIndex]->localMatrix();
			MeshList[meshIndex]->draw();

		}

		fbo->unbind();
		passthroughGS->unsuse();
		normalGS->unsuse();
		renderToTexture(materialRTT, fbo);

		// Swap buffers
		glfwSwapBuffers(window);
		glFlush();

		glfwPollEvents();
	} // Check if the ESC key was pressed or the window was closed
	while (!glfwWindowShouldClose(window));

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

static void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	/*else if (key != GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
	}*/
		computeMotion(window, key, action);
}

void computeMotion(GLFWwindow* window, int key, int action)
{
	static double lastTime = glfwGetTime();
	static double hAngle = glm::pi<double>();
	static double vAngle = 0.0;
	static double fov = 45.0;

	static float speed = 3.0f;
	static float mouseSpeed = 0.005f;

	double currentTime = glfwGetTime();
	float deltaTime = 0.02;//float(currentTime - lastTime);

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	glfwSetCursorPos(window, 1024 / 2, 768 / 2);

	hAngle += mouseSpeed * float(1024.0 / 2.0 - (float)xpos);
	vAngle += mouseSpeed * float(768.0 / 2.0 - (float)ypos);

	glm::vec3 direction(cos(vAngle) * sin(hAngle),
		sin(vAngle),
		cos(vAngle) * cos(hAngle));

	glm::vec3 right(sin(hAngle - glm::pi<float>() / 2.0),
		0.0,
		cos(hAngle - glm::pi<float>() / 2.0));

	glm::vec3 position = gCamera->from();


	if (key == GLFW_KEY_UP)
		position += direction * deltaTime * speed;

	else if (key == GLFW_KEY_DOWN)
		position -= direction * deltaTime * speed;

	else if (key == GLFW_KEY_RIGHT)
		position += right * deltaTime * speed;

	else if (key == GLFW_KEY_LEFT)
		position -= right * deltaTime * speed;

	else if (key == GLFW_KEY_P)
		gCamera->setType(Camera::PERSPECTIVE);

	else if (key == GLFW_KEY_O)
		gCamera->setType(Camera::ORTHOGRAPHIC);

	else if (key == GLFW_KEY_R && action == GLFW_PRESS)
	{
		if (whatRender == 2)
			whatRender = 0;
		else
			++whatRender;
	}

	else if (key == GLFW_KEY_N && action == GLFW_PRESS)
	{
		showNormal = !showNormal;
	}

	glm::vec3 up = glm::cross(right, direction);

	gCamera->setFrom(position);
	gCamera->setTo(position + direction);
	gCamera->setUp(glm::vec3(0.0, 1.0, 0.0));

	lastTime = currentTime;
}

