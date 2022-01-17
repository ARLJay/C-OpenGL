#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <string.h>

#include <shader.h>
#include <ortho.h>
#include <view.h>
#include <obj.h>

static float zoom = 1.0f;
static float x = 1.0f;
static float y = 1.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		y += 0.05f;
	}
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		y -= 0.05f;
	}
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		x += 0.05f;
	}
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		x -= 0.05f;
	}
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	if(yoffset < 0)
	{
		zoom += 0.05f;
	} else {
		zoom -= 0.05f;
	}
}

int main(int argc, char *argv[])
{
	glfwInit();

	const char* title = "C";

	GLFWwindow* window = glfwCreateWindow(800, 600, title, NULL, NULL);

	if(window == NULL)
	{
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD\n");
    return -1;
	}

//	float positions[] = {
//		-1.5f, -0.5f,
//		-0.5f, -0.5f,
//		-0.5f, 0.5f,
//		-1.5f, 0.5f,
//
//		0.5f, -0.5f,
//		1.5f, -0.5f,
//		1.5f, 0.5f,
//		0.5f, 0.5f
//	};

	CreateObject(1.25f, -5.0f, 0.5f, 0.5f, 1.0f);

	float positions[8 * ReturnObjects()->Count];
	memcpy(positions, ReturnObjects()->Positions, 8 * ReturnObjects()->Count * sizeof(float));

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0//,

		//4, 5, 6,
		//6, 7, 4
	};

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	unsigned int va;
	glCreateVertexArrays(1, &va);
	glBindVertexArray(va);

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW);
	//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	unsigned int ib;
	glGenBuffers(1, &ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);


	glViewport(0, 0, 800, 600);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetScrollCallback(window, scroll_callback);

	unsigned int shader = CreateShader("assets/shaders/vert.glsl", "assets/shaders/frag.glsl");
	glUseProgram(shader);


	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		ApplyGravity(0.05f);
		memcpy(positions, ReturnObjects()->Positions, 8 * ReturnObjects()->Count * sizeof(float));
		
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);


		//Camera
		//-aspect * zoom, aspect * zoom, -zoom, zoom
 		setOrthoMatrix(shader, -5.0*zoom, 5.0*zoom, -5.0*zoom, 5.0*zoom, 0.0f, 10.0f);
		setViewMatrix(shader, x, y);

		processInput(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
