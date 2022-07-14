/**
 * @author Andrej Bartulin
 * PROJECT: Termi-Linux version with OpenGL and Dear ImGui rendering system
 * LICENSE: ringwormGO General License 1.0 | (RGL) 2022
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

int width;
int height;

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

int main(int argc, char **argv)
{
	std::cout << "\n\n";

	bool arg = false;
	bool alreadyarg = false;

	if (argc > 1)
	{
		render.startup_command = argv[1];
		arg = true;
	}

	/* Catch CTRL-C */
	sigIntHandler.sa_handler = end;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;
	sigaction(SIGINT, &sigIntHandler, NULL);


    std::cout << "ooooooooooo                              " << std::endl;
    std::cout << "    888      ooooooooooo                          o88   " << std::endl;
    std::cout << "    888      888    88  oo oooooo  oo ooo oooo   oooo  " << std::endl;
    std::cout << "    888      888ooo8     888    888 888 888 888   888 " << std::endl;
    std::cout << "    888      888    oo   888        888 888 888   888  " << std::endl;
    std::cout << "   o888o    o888ooo8888 o888o      o888o888o888o o888o " << std::endl;
    std::cout << "------------------------------------------------------- " << std::endl;

	glfwInit();
	GLFWwindow* window = glfwCreateWindow(render.Settings(1, 0), render.Settings(2, 0), "Termi (OpenGL)", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if (window == NULL)
	{
		std::cout << "Unable to create OpenGL window!\nExiting...\n";
		return 1;
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

	/* Initialize Dear ImGui */
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	render.Settings(3, 0);
	
	if (render.font_name != "default")
	{
		try
		{
			if (render.CheckFile(render.font_name.c_str()) == 0)
			{
				io.Fonts->AddFontFromFileTTF(render.font_name.c_str(), render.Settings(4, 0));
			}
		}
		catch(const std::exception& e)
		{
			std::cerr << "Exception catched! Result: " << e.what() << '\n';
		}
	}

	render.Settings(0, 0);

	if (render.startup_command != "none")
	{
		arg = true;
	}

	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		/* Tell OpenGL a new frame is about to begin */
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		glfwGetWindowSize(window, &width, &height);
		window_width = static_cast<float>(width);
		window_height = static_cast<float>(height);

		ImGui::SetNextWindowPos(ImVec2(pos_x, pos_y));
    	ImGui::SetNextWindowSize(ImVec2(window_width, window_height));

		/* main Dear ImGui code */
		main_code();

		if (arg && !alreadyarg)
		{
			console.ExecCommand(render.startup_command, argv[2]);
			alreadyarg = true;
		}

		#ifdef PRINT_FPS
			printf("Application average %.3f ms/frame (%.1f FPS)\r", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		#endif

		/* Renders the Dear ImGui elements */
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
