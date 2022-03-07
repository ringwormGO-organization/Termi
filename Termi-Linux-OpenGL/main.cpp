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

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Canvas canvas;

int main()
{
	std::cout << "\n\n";

	canvas.width = 900;
	canvas.height = 900;

	glfwInit();
	GLFWwindow* window = glfwCreateWindow(canvas.width, canvas.height, "Termi (OpenGL)", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	/*
	//load image
	int width, height;
	int channels; // number of color components. Example: RGB has 3 color components.
	unsigned char* pixels = stbi_load("termi.png", &width, &height, &channels, 4);

	// change window icon
	GLFWimage images[1];
	images[0].width = width;
	images[1].height = height;
	images[2].pixels = pixels;

	glfwSetWindowIcon(window, 1, images); 
	*/ 
	//code is commented because it is couse segmentation fault

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
