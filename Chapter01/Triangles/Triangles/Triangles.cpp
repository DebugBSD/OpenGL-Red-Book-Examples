// Triangles.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
using namespace std;

#include "vgl.h"
#include "LoadShaders.h"

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs {ArrayBuffer, NumBuffers};
enum Attrib_IDs { vPosition = 0 };

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6;

void init()
{
	static const GLfloat vertices[NumVertices][2] =
	{
		{ -0.90, -0.90 }, // First Triangle
		{  0.85, -0.90 },
		{ -0.90,  0.85 },
		{  0.90, -0.85 }, // Second Triangle
		{  0.90,  0.90 },
		{ -0.85,  0.90 }
	};

	glCreateBuffers(NumBuffers, Buffers);
	glNamedBufferStorage(Buffers[ArrayBuffer], sizeof(vertices), vertices, 0);

	ShaderInfo shaders[] =
	{
		{ GL_VERTEX_SHADER, "triangles.vert" },
		{ GL_FRAGMENT_SHADER, "triangles.frag" },
		{ GL_NONE, NULL}
	};

	GLuint program = LoadShaders(shaders);
	glUseProgram(program);
	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vPosition);

}

void display(void)
{
	static const GLfloat black[] = {0.0f, 0.0f, 0.0, 0.0f};
	glClearBufferfv(GL_COLOR, 0, black);
	glBindVertexArray(VAOs[Triangles]);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);
}

int main()
{
	glfwInit();

	GLFWwindow* pWindow = glfwCreateWindow(640, 480, "triangles", NULL, NULL);
	glfwMakeContextCurrent(pWindow);
	gl3wInit();

	init();

	while (!glfwWindowShouldClose(pWindow))
	{
		display();
		glfwSwapBuffers(pWindow);
		glfwPollEvents();
	}

	glfwDestroyWindow(pWindow);

	glfwTerminate();


	return EXIT_SUCCESS;
}
