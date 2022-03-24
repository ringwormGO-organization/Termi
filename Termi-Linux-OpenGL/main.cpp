/**
 * @author Andrej Bartulin
 * PROJECT: Termi-Linux version with OpenGL and ImGUI rendering system
 * LICENSE: BSD-3-Clause-License
 * DESCRIPTION: Main file
 * INFORAMTION: Install OpenGL and run this command in terminal: clear && cmake . && sudo make && ./Termi-OpenGL
*/

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "imgui_code.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <signal.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Settings.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct sigaction sigIntHandler;

void end(int sig)
{
	std::cout << "\nPress any key to continue...\n";
    auto key = std::cin.get();
    if (key != 10)
    {
        /* we need to do something here; input is broken */
        exit(0);
    }
    else
    {
        exit(sig);
    }
}

int main()
{
	std::cout << "\n\n";

	/* Catch CTRL-C */
	sigIntHandler.sa_handler = end;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;
	sigaction(SIGINT, &sigIntHandler, NULL);

	glfwInit();
	GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Termi (OpenGL)", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if (window == NULL)
	{
		std::cout << "Unable to create OpenGL window!\nExiting...\n";
		return 0;
	}
	else
	{
		#ifdef PRINT_WHEN_WINDOW_IS_CREATED
			std::cout << "OpenGL window is created.\n";
		#endif
	}


	GLFWimage images[1];
	images[0].pixels = stbi_load("termi.png", &images[0].width, &images[0].height, 0, 4); //rgba channels 
	glfwSetWindowIcon(window, 1, images);
	stbi_image_free(images[0].pixels);

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

		/*ImGui demo window */
		if (isDemoWindow == true)
		{
			ImGui::ShowDemoWindow();
		}

		#ifdef PRINT_FPS
			printf("Application average %.3f ms/frame (%.1f FPS)\r", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		#endif

		/* Renders the ImGUI elements */
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
