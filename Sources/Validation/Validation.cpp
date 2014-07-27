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


#include "../Engine/GL/ShaderPipeline.h"
#include "../Engine/LoaderObj/LoaderObj.h"
#include "../Engine/Mesh/Mesh.h"
#include "../Engine/GL/FrameBufferObject.h"
#include "../Engine/Camera/Camera.h"
#include "../Engine/Light/PointLight.h"
#include "../Engine/Texture/CubeMap.h"
#include "../Engine/Mesh/MeshTools.h"

static void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
void computeMotion(GLFWwindow* window, int key, int action);

using namespace Good;

ViewportPtr gViewport = nullptr;
CameraPtr gCamera = nullptr;

int whatRender = 0;
bool showNormal = false;
bool rotate = false;
bool showVoxel = false;

struct WorldTransform
{
	glm::mat4 modelMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	glm::mat4 normalMatrix;
};

void renderToTexture(MaterialPtr material, FrameBufferObjectPtr fbo);
void render(const MeshesList& list, FrameBufferObjectPtr fbo, GLuint bufferID);
void renderShadowMap(const MeshesList& list, FrameBufferObjectPtr shadowMap, ISceneNodePtr light, ShaderProgramPtr program, GLuint bufferID);

void renderShadowMap(const MeshesList& list, FrameBufferObjectPtr shadowMap, ISceneNodePtr light, ShaderProgramPtr program, GLuint bufferID)
{
	shadowMap->bind();
	program->use();

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int meshIndex = 0; meshIndex < list.size(); ++meshIndex)
	{
		list[meshIndex]->material()->use();
		glm::mat4 view = glm::lookAt(light->position(), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		glBindBufferBase(GL_UNIFORM_BUFFER, 0, bufferID);
		WorldTransform *transform = (WorldTransform*)glMapBufferRange(GL_UNIFORM_BUFFER, 0, sizeof(WorldTransform), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

		transform->modelMatrix = list[meshIndex]->localMatrix();
		transform->viewMatrix = view;
		transform->projectionMatrix = glm::frustum(-1.0f, 1.0f, -1.0f, 1.0f, gCamera->zMin(), gCamera->zMax());
		glm::mat4 modelView = view * list[meshIndex]->localMatrix();
		transform->normalMatrix = glm::transpose(glm::inverse(modelView));

		glUnmapBuffer(GL_UNIFORM_BUFFER);

		list[meshIndex]->draw();
	}

	shadowMap->unbind();
}

void render(const MeshesList& list, FrameBufferObjectPtr fbo, GLuint bufferID)
{
	fbo->bind();
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int meshIndex = 0; meshIndex < list.size(); ++meshIndex)
	{		
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, bufferID);
		WorldTransform *transform = (WorldTransform*)glMapBufferRange(GL_UNIFORM_BUFFER, 0, sizeof(WorldTransform), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

		transform->modelMatrix = list[meshIndex]->localMatrix();
		transform->viewMatrix = gCamera->viewMatrix();
		transform->projectionMatrix = gCamera->projectionMatrix();
		glm::mat4 modelView = gCamera->viewMatrix() * list[meshIndex]->localMatrix();
		transform->normalMatrix = glm::transpose(glm::inverse(modelView));

		glUnmapBuffer(GL_UNIFORM_BUFFER);
		list[meshIndex]->draw();
	}
	fbo->unbind();
}
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

	bool depthMode = false;

	glActiveTexture(GL_TEXTURE0);

	switch (whatRender)
	{
	case 0:
		glBindTexture(GL_TEXTURE_2D, fbo->buffer());
		break;
	case 1:
		glBindTexture(GL_TEXTURE_2D, fbo->buffer(1));
		break;
	case 2:
		glBindTexture(GL_TEXTURE_2D, fbo->buffer(2));
		break;
	case 3:
		glBindTexture(GL_TEXTURE_2D, fbo->buffer(3));
		break;
	case 4:
		glBindTexture(GL_TEXTURE_2D, fbo->depthBuffer());
		depthMode = true;
		break;
	}


	GLint texLoc = glGetUniformLocation(fragmentShader->id(), "tex0");
	GLint linearise = glGetUniformLocation(fragmentShader->id(), "linearize");

	glProgramUniform1i(fragmentShader->id(), texLoc, 0);
	glProgramUniform1i(fragmentShader->id(), linearise, depthMode);

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

	ShaderPipelinePtr pipeline(new ShaderPipeline);

	ShaderProgramPtr passthroughVS(new ShaderProgram(pipeline, "X:\\DevGit\\Good-Engine\\Applications\\Shaders\\Passthrough.vert", GL_VERTEX_SHADER, "passthroughVS"));
	ShaderProgramPtr passthroughGS(new ShaderProgram(pipeline, "X:\\DevGit\\Good-Engine\\Applications\\Shaders\\Passthrough.geom", GL_GEOMETRY_SHADER, "passthroughGS"));
	ShaderProgramPtr passthroughFS(new ShaderProgram(pipeline, "X:\\DevGit\\Good-Engine\\Applications\\Shaders\\Passthrough.frag", GL_FRAGMENT_SHADER, "passthroughFS"));

	ShaderProgramPtr lightFS(new ShaderProgram(pipeline, "X:\\DevGit\\Good-Engine\\Applications\\Shaders\\Material.frag", GL_FRAGMENT_SHADER, "lightFS"));
	ShaderProgramPtr lightGS(new ShaderProgram(pipeline, "X:\\DevGit\\Good-Engine\\Applications\\Shaders\\Light.geom", GL_GEOMETRY_SHADER, "lightGS"));

	ShaderProgramPtr textureVS(new ShaderProgram(pipeline, "X:\\DevGit\\Good-Engine\\Applications\\Shaders\\RenderToTexture.vert", GL_VERTEX_SHADER, "rttVS"));
	ShaderProgramPtr textureFS(new ShaderProgram(pipeline, "X:\\DevGit\\Good-Engine\\Applications\\Shaders\\RenderToTexture.frag", GL_FRAGMENT_SHADER, "rttFS"));

	ShaderProgramPtr normalGS(new ShaderProgram(pipeline, "X:\\DevGit\\Good-Engine\\Applications\\Shaders\\NormalViewer.geom", GL_GEOMETRY_SHADER, "normalGS"));
	
	ShaderProgramPtr cubeMapGS(new ShaderProgram(pipeline, "X:\\DevGit\\Good-Engine\\Applications\\Shaders\\CubeMapEnv.geom", GL_GEOMETRY_SHADER, "CubeMapEnvGS"));
	ShaderProgramPtr cubeMapFS(new ShaderProgram(pipeline, "X:\\DevGit\\Good-Engine\\Applications\\Shaders\\CubeMapEnv.frag", GL_FRAGMENT_SHADER, "CubeMapEnvFS"));

	if (!pipeline->isValid())
	{
		glfwTerminate();
		return -5;
	}

	CubeMapPtr env(new CubeMap);

	MaterialPtr materialRed(new Material(passthroughVS, lightFS, lightGS));

	MaterialPtr materialGreen(new Material(passthroughVS, lightFS, lightGS));
	materialGreen->data.diffuseColor = glm::vec4(0.0, 1.0, 0.0, 1.0);
	materialGreen->env = env;

	MaterialPtr materialBlue(new Material(passthroughVS, lightFS, lightGS));
	materialBlue->data.diffuseColor = glm::vec4(0.0, 0.0, 1.0, 1.0);

	MaterialPtr materialEnv(new Material(passthroughVS, cubeMapFS, cubeMapGS));
	materialEnv->env = env;

	MaterialPtr materialRTT(new Material(textureVS, textureFS));

	std::vector<MeshPtr> meshesList;

	ILoader* loader = new LoaderObj;
	MeshPtr suzanne = loader->load("X:\\DevGit\\Good-Engine\\Applications\\Objects\\SuzanneHP.obj");
	suzanne->setMaterial(materialRed);
	suzanne->setPosition(glm::vec3(-3.0, 0.0, 0.0));

	MeshPtr sphere = MeshTools::createSphere(32, 32);
	sphere->setMaterial(materialBlue);
	sphere->setPosition(0.0, -1.0, -5.0);

	MeshPtr sphere2 = MeshTools::createSphere(32, 32);
	sphere2->setMaterial(materialGreen);
	sphere2->setPosition(5.0, 0.0, -1.0);

	MeshPtr cube = loader->load("X:\\DevGit\\Good-Engine\\Applications\\Objects\\Cube.obj");
	cube->setMaterial(materialEnv);
	cube->cullface(false);
	
	meshesList.push_back(suzanne);
	meshesList.push_back(sphere);
	meshesList.push_back(sphere2);

	gViewport = ViewportPtr(new Viewport(0, 0, 1024, 768));
	gCamera = CameraPtr(new Camera(gViewport));
	gCamera->setFrom(glm::vec3(0.0, 0.0, 10.0));

	FrameBufferObjectPtr fbo(new FrameBufferObject(GL_TEXTURE_2D, 4, gViewport->width(), gViewport->height()));

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	GLuint bufferID;
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_UNIFORM_BUFFER, bufferID);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(WorldTransform), NULL, GL_DYNAMIC_DRAW);

	PointLightPtr light(new PointLight("light", nullptr));
	light->setPosition(5.0, 5.0, 5.0);

	float angle = 1.0;
	float xFactor = 0.0;

	do{
		if (showNormal)
		{
			for(int idx = 0; idx < meshesList.size(); ++idx)
				meshesList[idx]->material()->_geometryShader = normalGS;
		}
		else
		{			
			for(int idx = 0; idx < meshesList.size(); ++idx)
				meshesList[idx]->material()->_geometryShader = lightGS;
		}

		if (rotate)
			suzanne->yaw(angle);

		render(meshesList, fbo, bufferID);
		renderToTexture(materialRTT, fbo);

		glfwSwapBuffers(window);
		glFlush();

		glfwPollEvents();
	} while (!glfwWindowShouldClose(window));

	glfwTerminate();

	return 0;
}

static void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

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
	glm::vec3 up = glm::cross(right, direction);

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
		if (whatRender == 4)
			whatRender = 0;
		else
			++whatRender;
	}

	else if (key == GLFW_KEY_N && action == GLFW_PRESS)
		showNormal = !showNormal;
	else if (key == GLFW_KEY_T && action == GLFW_PRESS)
		rotate = !rotate;
	else if (key == GLFW_KEY_V && action == GLFW_PRESS)
		showVoxel = !showVoxel;

	else if (key == GLFW_KEY_PAGE_UP)
	{
		position += up * deltaTime * speed;
	}
	else if (key == GLFW_KEY_PAGE_DOWN)
	{
		position -= up * deltaTime * speed;
	}



	gCamera->setFrom(position);
	gCamera->setTo(position + direction);
	gCamera->setUp(glm::vec3(0.0, 1.0, 0.0));

	lastTime = currentTime;
}

