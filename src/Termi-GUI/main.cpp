/**
 * @author Andrej Bartulin
 * PROJECT: Termi version with OpenGL and Dear ImGui rendering system
 * LICENSE: ringwormGO General License 1.0 | (RGL) 2022
 * DESCRIPTION: Main file
 * INFORAMTION: Install OpenGL and run this command in terminal: clear && cmake . && make && ./Termi-OpenGL
 */

/* Dear ImGui includes */
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

/* Standard library includes */
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <thread>

#ifdef _WIN32
	#include <Windows.h>
#elif _WIN64
    #include <Windows.h>
#elif __APPLE__ || __MACH__
	#include <signal.h>
#elif __linux__
	#include <signal.h>
#elif __FreeBSD__
	#include <signal.h>
#endif

/* stb_image include */
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

/* We need this include to be right here */
#include "Settings.hpp"

/* Glad include */
#ifdef USE_PREINSTALLED_HEADERS
	#include "includes/glad.h"
#else
	#include <glad/glad.h>
#endif

/* Termi's includes except Settings.hpp */
#include "imgui_code.hpp"

/* GLFW 3 include */
#ifdef _WIN32
	#include "includes/GLFW/glfw3.h"
#elif _WIN64
	#include "includes/GLFW/glfw3.h"
#else
	#include <GLFW/glfw3.h>
#endif

int width = 0;
int height = 0;

#ifdef _WIN32
	static BOOL WINAPI end(DWORD dwCtrlType)
	{
		int key;

		switch (dwCtrlType)
		{
		case CTRL_C_EVENT: // Ctrl+C
			std::cout << "\nPress any key to continue...\n";
			key = std::cin.get();
			if (key != 10)
			{
				/* we need to do something here; input is broken */
				exit(0);
			}
			else
			{
				exit(0);
			}
			break;
		case CTRL_BREAK_EVENT: // Ctrl+Break
			break;
		case CTRL_CLOSE_EVENT: // Closing the console window
			break;
		case CTRL_LOGOFF_EVENT: // User logs off. Passed only to services!
			break;
		case CTRL_SHUTDOWN_EVENT: // System is shutting down. Passed only to services!
			break;
		}

		// Return TRUE if handled this message, further handler functions won't be called.
		// Return FALSE to pass this message to further handlers until default handler calls ExitProcess().
		return FALSE;
	}
#elif _WIN64
	static BOOL WINAPI end(DWORD dwCtrlType)
	{
		int key;

		switch (dwCtrlType)
		{
		case CTRL_C_EVENT: // Ctrl+C
			std::cout << "\nPress any key to continue...\n";
			key = std::cin.get();
			if (key != 10)
			{
				/* we need to do something here; input is broken */
				exit(0);
			}
			else
			{
				exit(0);
			}
			break;
		case CTRL_BREAK_EVENT: // Ctrl+Break
			break;
		case CTRL_CLOSE_EVENT: // Closing the console window
			break;
		case CTRL_LOGOFF_EVENT: // User logs off. Passed only to services!
			break;
		case CTRL_SHUTDOWN_EVENT: // System is shutting down. Passed only to services!
			break;
		}

		// Return TRUE if handled this message, further handler functions won't be called.
		// Return FALSE to pass this message to further handlers until default handler calls ExitProcess().
		return FALSE;
	}
#elif __APPLE__ || __MACH__
	struct sigaction sigIntHandler;

	void end(int sig)
	{
		std::cout << "\nPress any key to continue...\n";
		auto key = std::cin.get();
		if (key != 10)
		{
			/* we need to do something here; input is broken */
			exit(sig);
		}

		else
		{
			exit(sig);
		}
	}
#elif __linux__
	struct sigaction sigIntHandler;

	void end(int sig)
	{
		std::cout << "\nPress any key to continue...\n";
		auto key = std::cin.get();
		if (key != 10)
		{
			/* we need to do something here; input is broken */
			exit(sig);
		}

		else
		{
			exit(sig);
		}
	}
#elif __FreeBSD__
	struct sigaction sigIntHandler;

	void end(int sig)
	{
		std::cout << "\nPress any key to continue...\n";
		auto key = std::cin.get();
		if (key != 10)
		{
			/* we need to do something here; input is broken */
			exit(sig);
		}

		else
		{
			exit(sig);
		}
	}
#endif

void tmain()
{
	std::cout << "\n\n";

	/*
	 * Creating variables which points to struct(s) or class(es)
	 * vars gets value once,
	 * while render is always getting value
	 */

	Vars *vars = new Vars();
	vars->language = "english";

	Renderer *render = new Renderer();
	bool iconReady = false;

	#ifdef _WIN32
		/* Catch CTRL-C */
		SetConsoleCtrlHandler(end, TRUE);
    #elif _WIN64
		/* Catch CTRL-C */
		SetConsoleCtrlHandler(end, TRUE);
    #elif __APPLE__ || __MACH__
		/* Catch CTRL-C */
		sigIntHandler.sa_handler = end;
		sigemptyset(&sigIntHandler.sa_mask);
		sigIntHandler.sa_flags = 0;
		sigaction(SIGINT, &sigIntHandler, NULL);
    #elif __linux__
		/* Catch CTRL-C */
		sigIntHandler.sa_handler = end;
		sigemptyset(&sigIntHandler.sa_mask);
		sigIntHandler.sa_flags = 0;
		sigaction(SIGINT, &sigIntHandler, NULL);
    #elif __FreeBSD__
		/* Catch CTRL-C */
		sigIntHandler.sa_handler = end;
		sigemptyset(&sigIntHandler.sa_mask);
		sigIntHandler.sa_flags = 0;
		sigaction(SIGINT, &sigIntHandler, NULL);
    #endif

	std::cout << "ooooooooooo                              " << std::endl;
	std::cout << "    888      ooooooooooo                          o88   " << std::endl;
	std::cout << "    888      888    88  oo oooooo  oo ooo oooo   oooo  " << std::endl;
	std::cout << "    888      888ooo8     888    888 888 888 888   888 " << std::endl;
	std::cout << "    888      888    oo   888        888 888 888   888  " << std::endl;
	std::cout << "   o888o    o888ooo8888 o888o      o888o888o888o o888o " << std::endl;
	std::cout << "------------------------------------------------------- " << std::endl;

	if (render->CheckFile("termi.png") == false)
	{
		std::cout << "Icon wasn't found!\n";
		std::cout << "Do you want download it [y (requires curl) /n]? : " << std::endl;

		std::string yn;
		std::cin >> yn;

		if (yn == "y")
		{
			system("wget https://raw.githubusercontent.com/ringwormGO-organization/Termi/main/Termi-OpenGL/termi.png");

			if (render->CheckFile("termi.png"))
			{
				iconReady = true;
			}
		}
	}

	else
	{
		iconReady = true;
	}

	glfwInit();
	GLFWwindow *window = glfwCreateWindow(render->Settings(1, 0), render->Settings(2, 0), "Termi (OpenGL)", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if (window == NULL)
	{
		std::cout << "Unable to create OpenGL window!\nExiting...\n";
		return;
	}

	else
	{
#ifdef PRINT_WHEN_WINDOW_IS_CREATED
		std::cout << "OpenGL window is created.\n";
#endif
	}

	if (iconReady)
	{
		GLFWimage images[1];
		images[0].pixels = stbi_load("termi.png", &images[0].width, &images[0].height, 0, 4); /* rgba channels */
		glfwSetWindowIcon(window, 1, images);
		stbi_image_free(images[0].pixels);
	}

	else
	{
		std::cout << "Continuing without an icon!\n";
	}

	/* Initialize Dear ImGui */
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO &io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGuiStyle& style = ImGui::GetStyle();
	(void)style;

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	render->SetFont(io);
	render->Settings(0, 0);

	delete render;

	while (!glfwWindowShouldClose(window))
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
		main_code(style);

#ifdef PRINT_FPS_CONSOLE
		printf("Application average %.3f ms/frame (%.1f FPS)\r", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
#endif

		/* Renders the Dear ImGui elements */
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}
