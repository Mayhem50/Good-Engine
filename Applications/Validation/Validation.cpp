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

#include "../GoodCore/Core/ShaderPipeline.h"
#include "../GoodCore/Core/LoaderObj.h"
#include "../GoodCore/Core/Mesh.h"
#include "../GoodCore/Core/FrameBufferObject.h"
#include "../GoodCore/Core/Camera.h"
#include "../GoodCore/Core/MaterialPipeline.h"

static void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
void computeMotion(GLFWwindow* window, int key, int action);

using namespace Good;

ViewportPtr gViewport = nullptr;
CameraPtr gCamera = nullptr;
int whatRender = 0;
bool showNormal = false;
bool stopYaw = false;

void renderToTexture(ShaderPipelinePtr pipeline, FrameBufferObjectPtr fbo);

void renderToTexture(ShaderPipelinePtr pipeline, FrameBufferObjectPtr fbo)
{
	pipeline->use();

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
	ShaderProgramPtr fragmentShader = pipeline->fragmentShader();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//glViewport(0, 0, 1024, 768);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (whatRender)
	{
	case 0:
		glBindTexture(GL_TEXTURE_2D, fbo->colorBuffer(0));
		break;
	case 1:
		glBindTexture(GL_TEXTURE_2D, fbo->colorBuffer(1));
		break;
	case 2:
		glBindTexture(GL_TEXTURE_2D, fbo->colorBuffer(2));
		break;
	case 3:
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
		
	ShaderPipelinePtr renderToTexturePipeline(new ShaderPipeline);

	ShaderProgramPtr passthroughVS = ShaderProgram::CreateShaderProgramFromFile("../../Assets/Shaders/Passthrough.vert", GL_VERTEX_SHADER, "passthroughVS");
	ShaderProgramPtr textureFS = ShaderProgram::CreateShaderProgramFromFile("../../Assets/Shaders/SimpleTexture.frag", GL_FRAGMENT_SHADER, "textureFS");
	ShaderProgramPtr normalGS = ShaderProgram::CreateShaderProgramFromFile("../../Assets/Shaders/NormalViewer.geom", GL_GEOMETRY_SHADER, "normalGS");

	renderToTexturePipeline->addProgram(passthroughVS);
	renderToTexturePipeline->addProgram(textureFS);
	
	if (!renderToTexturePipeline->isValid())
		return -5;


	MaterialPipelinePtr materialPipeline(new MaterialPipeline);

	MaterialPtr plastic(new Material);
	MaterialPtr metal(new Material);

	metal->parameters.metalic = 1.0;


	std::vector<MeshPtr> MeshList;
	int nbMesh = 0;

	MeshPtr loadedMesh = GeometryLoader::load("..\\..\\Assets\\Objects\\suzanne.obj");
	loadedMesh->setPosition(glm::vec3(0.2, 0.0, -1.0));
	loadedMesh->setMaterial(plastic);
	loadedMesh->init();
	MeshList.push_back(loadedMesh);

	MeshPtr loadedMesh2 = GeometryLoader::load("..\\..\\Assets\\Objects\\suzanne.obj");
	loadedMesh2->setPosition(glm::vec3(2, 1, -2.0));
	loadedMesh2->setMaterial(metal);
	loadedMesh2->init();
	MeshList.push_back(loadedMesh2);

	/*MeshPtr loadedMesh3 = GeometryLoader::load("..\\..\\Assets\\Objects\\sphere.obj");
	loadedMesh3->setPosition(glm::vec3(-3, 0.5, -2.0));
	loadedMesh3->setMaterial(material);
	loadedMesh3->init();
	MeshList.push_back(loadedMesh3);*/
	
	gViewport = ViewportPtr(new Viewport(0, 0, 1024, 768));
	gCamera = CameraPtr(new Camera(gViewport));

	FrameBufferObjectPtr fbo(new FrameBufferObject(3, gViewport->width(), gViewport->height()));

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

		//if (showNormal)
		//	normalGS->use();
		//else
		//	passthroughGS->use();

		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		for (auto mesh : MeshList)
		{
			if (!stopYaw)
				mesh->yaw(angle);
						
			materialPipeline->update(mesh, gCamera);
			
			glm::mat4 localToWorldMatrix = mesh->localMatrix();
			mesh->draw();
		}

		fbo->unbind();
		renderToTexture(renderToTexturePipeline, fbo);

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
	if (key == GLFW_KEY_P)
	{
		gCamera->setType(Camera::PERSPECTIVE);
		return;
	}

	else if (key == GLFW_KEY_O)
	{
		gCamera->setType(Camera::ORTHOGRAPHIC);
		return;
	}

	else if (key == GLFW_KEY_R && action == GLFW_PRESS)
	{
		if (whatRender == 3)
			whatRender = 0;
		else
			++whatRender;

		return;
	}

	else if (key == GLFW_KEY_N && action == GLFW_PRESS)
	{
		showNormal = !showNormal;
		return;
	}

	else if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		stopYaw = !stopYaw;
		return;
	}

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

	glm::vec3 up = glm::cross(right, direction);

	gCamera->setFrom(position);
	gCamera->setTo(position + direction);
	gCamera->setUp(glm::vec3(0.0, 1.0, 0.0));

	lastTime = currentTime;
}

