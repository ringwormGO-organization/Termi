/**
 * @author Andrej Bartulin
 * @mainteiner Stjepan Bilić Matišić
 * PROJECT: Termi-linux version with OpenGL and ImGUI rendering system
 * LICENSE: BSD-3-Clause-License
 * DESCRIPTION: Main file
 * INFORAMTION: Install OpenGL and run this command in terminal: clear && cmake . && sudo make && ./Termi-OpenGL
*/

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "imgui_code.hpp"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define WIDTH 900
#define HEIGHT 900

int main()
{
	std::cout << "\n\n";

	glfwInit();
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Termi (independet version; OpenGL and Dear ImGUI", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	/* Initialize ImGUI */
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		/* Tell OpenGL a new frame is about to begin */
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		/* main ImGUI code */
		main_code();

		/* Renders the ImGUI elements */
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
