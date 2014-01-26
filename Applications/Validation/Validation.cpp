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

#include "../GoodCore/Core/GLSLProgram.h"
#include "../GoodCore/Core/LoaderObj.h"
#include "../GoodCore/Core/Mesh.h"

static void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
void computeMotion(GLFWwindow* window, int key, int action);

using namespace Good;

ViewportPtr gViewport = nullptr;
CameraPtr gCamera = nullptr;

int main(int argc, char* argv[])
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

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

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetKeyCallback(window, keyCallback);

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

	std::vector<Mesh*> MeshList;
	int nbMesh = 1;

	GLSLProgramPtr shader(new GLSLProgram("../Shaders/TransformVertexShader.glsl", "../Shaders/ColorFragmentShader.glsl"));

	for (int idMesh = 0; idMesh < nbMesh; ++idMesh)
	{
		Mesh* mesh = new Mesh();

		for (int idx = 0; idx < sizeof(cubeBufferData) / 4; idx += 3)
		{
			Vertex vertex;

			vertex.position = glm::vec3(cubeBufferData[idx], cubeBufferData[idx + 1], cubeBufferData[idx + 2]);
			mesh->addVertex(vertex);
		}


		mesh->setShaders(shader);
		float posFactor = 0.1f * (float)idMesh;
		mesh->setPosition(glm::vec3(posFactor));
		mesh->setScale(glm::vec3(0.5));
		mesh->init();

		MeshList.push_back(mesh);
	}


	gViewport = ViewportPtr(new Viewport(0, 0, 1024, 768));
	gCamera = CameraPtr(new Camera(gViewport));

	do{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (int idx = 0; idx < nbMesh; ++idx)
		{
			MeshList[idx]->render(gCamera);
		}
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

	else if (key != GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		computeMotion(window, key, action);
	}
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
	float deltaTime = float(currentTime - lastTime);

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	glfwSetCursorPos(window, 1024 / 2, 768 / 2);

	hAngle += mouseSpeed * float(1024 / 2 - xpos);
	vAngle += mouseSpeed * float(768 / 2 - ypos);

	glm::vec3 direction(cos(vAngle) * sin(hAngle),
		sin(vAngle),
		cos(vAngle) * cos(hAngle));

	glm::vec3 right(sin(hAngle - glm::pi<float>() / 2.0),
		0.0,
		cos(hAngle - glm::pi<float>() / 2.0));

	glm::vec3 up = glm::cross(right, direction);
	glm::vec3 position = gCamera->from();


	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		position += direction * deltaTime * speed;
	}

	else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		position -= direction * deltaTime * speed;
	}

	else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		position += right * deltaTime * speed;
	}

	else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
	{
		position -= right * deltaTime * speed;
	}

	else if (key == GLFW_KEY_P && action == GLFW_PRESS)
		gCamera->setType(Camera::PERSPECTIVE);

	else if (key == GLFW_KEY_O && action == GLFW_PRESS)
		gCamera->setType(Camera::ORTHOGRAPHIC);

	gCamera->setFrom(position);
	gCamera->setTo(direction);
	gCamera->setUp(up);

	lastTime = currentTime;
}

