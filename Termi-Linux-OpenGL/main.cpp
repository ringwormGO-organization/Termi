/**
 * @author Andrej Bartulin
 * @mainteiner Stjepan Bilić Matišić
 * PROJECT: Termi-linux version with OpenGL and ImGUI rendering system
 * LICENSE: BSD-3-Clause-License
 * DESCRIPTION: Main file
 * INFORAMTION: Install OpenGL and run this command in terminal: clear && cmake . && sudo make && ./Termi-OpenGL
*/

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define WIDTH 800
#define HEIGHT 800

int main()
{
	std::cout << "\n\n";

	glfwInit();
	GLFWwindow* w = glfwCreateWindow(WIDTH, HEIGHT, "Termi (independet version; OpenGL and Dear ImGUI", NULL, NULL);
	glfwMakeContextCurrent(w);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	float t[] =
	{
		-.5f, -.5f, 0.f,
		0.f, .5f, 0.f,
		.5f, -.5f, 0.f
	};

	uint32_t v;
	glGenBuffers(1, &v);
	glBindBuffer(GL_ARRAY_BUFFER, v);
	glBufferData(GL_ARRAY_BUFFER, sizeof(t)*sizeof(t)/sizeof(t[0]),
		&t[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3,
		 (void*)0);
	glEnableVertexAttribArray(0);
	glViewport(0, 0, 600, 600);
	while(!glfwWindowShouldClose(w))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(w);
		glfwPollEvents();
	}
	glfwTerminate();
}

