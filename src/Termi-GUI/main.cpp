/**
 * @author Andrej Bartulin
 * PROJECT: Termi version with OpenGL and Dear ImGui rendering system
 * LICENSE: MIT
 * DESCRIPTION: Main file
 */

/* Dear ImGui includes */
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

/* Standard library includes */
#include <filesystem>
#include <iostream>
#include <string>

#if defined _WIN32 || defined _WIN64
	#include <Windows.h>
#elif defined __APPLE__ || defined __MACH__ || defined __linux__ || \
    defined __FreeBSD__ || defined __OpenBSD__ || defined __NetBSD__
	#include <signal.h>
#endif

/* stb_image include */
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

/* Glad include */
#if defined _WIN32 || defined _WIN64
	#include "Libraries/include/glad/glad.h"
#else
	#include <glad/glad.h>
#endif

/* Termi's includes */
#include "imgui_code.hpp"
#include "utils/settings.hpp"

/* GLFW 3 include */
#if defined _WIN32 || defined _WIN64
	#include "Libraries/include/GLFW/glfw3.h"
#else
	#include <GLFW/glfw3.h>
#endif

int width = 0;
int height = 0;

#if defined _WIN32 || defined _WIN64
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
#elif defined __APPLE__ || defined __MACH__ || defined __linux__ || \
    defined __FreeBSD__ || defined __OpenBSD__ || defined __NetBSD__
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

void SetFont(Settings& settings, ImGuiIO& io)
{
	std::string font_name = settings.GetFontName();
	std::string glyph_range_str = settings.GetGlyphRange();

	int font_size = settings.GetFontSize();

	if (glyph_range_str == "korean")
	{
		io.Fonts->AddFontFromFileTTF(font_name.c_str(), font_size, NULL, io.Fonts->GetGlyphRangesKorean());
	}

	else if (glyph_range_str == "chinese_full")
	{
		io.Fonts->AddFontFromFileTTF(font_name.c_str(), font_size, NULL, io.Fonts->GetGlyphRangesChineseFull());
	}

	else if (glyph_range_str == "chinese_simplified_common")
	{
		io.Fonts->AddFontFromFileTTF(font_name.c_str(), font_size, NULL, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
	}

	else if (glyph_range_str == "japanese")
	{
		io.Fonts->AddFontFromFileTTF(font_name.c_str(), font_size, NULL, io.Fonts->GetGlyphRangesJapanese());
	}

	else if (glyph_range_str == "cyrillic")
	{
		io.Fonts->AddFontFromFileTTF(font_name.c_str(), font_size, NULL, io.Fonts->GetGlyphRangesCyrillic());
	}

	else if (glyph_range_str == "thai")
	{
		io.Fonts->AddFontFromFileTTF(font_name.c_str(), font_size, NULL, io.Fonts->GetGlyphRangesThai());
	}

	else if (glyph_range_str == "vietnamese")
	{
		io.Fonts->AddFontFromFileTTF(font_name.c_str(), font_size, NULL, io.Fonts->GetGlyphRangesVietnamese());
	}

	else if (glyph_range_str == "latin-ex-a")
	{
		/* Source of code: https://github.com/kmar/Sweet16Font/blob/master/Sweet16_ImGui.inl */
		static const ImWchar Sweet16_ranges[] =
		{
			0x0020,
			0x017F, // Basic Latin + Latin supplement + Latin extended A
			0,
		};

		ImFontConfig config;
		config.OversampleH = 1;
		config.OversampleV = 1;
		config.PixelSnapH = true;
		config.SizePixels = 16;
		// the proportional variant probably looks better with 1px extra horizontal spacing (just uncomment the following line)
		// config.GlyphExtraSpacing.x = 1;

		// copy font name manually to avoid warnings
		const char* name = "font/Sweet16.ttf, 16px";
		char* dst = config.Name;

		while (*name)
			*dst++ = *name++;
		*dst = '\0';

		io.Fonts->AddFontFromMemoryCompressedBase85TTF(Sweet16_compressed_data_base85, config.SizePixels, &config, Sweet16_ranges);
	}

	else
	{
		/* ignore */
	}
}

void tmain()
{
	std::cout << "\n\n";

	Settings settings;
	bool iconReady = false;

	/* Catch CTRL-C */
	#if defined _WIN32 || defined _WIN64
		SetConsoleCtrlHandler(end, TRUE);
    #elif defined __APPLE__ || defined __MACH__ || defined __linux__ || \
        defined __FreeBSD__ || defined __OpenBSD__ || defined __NetBSD__
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

	std::string icon_path = "termi.png";
	if (!std::filesystem::exists(icon_path) || !std::filesystem::is_regular_file(icon_path))
	{
		std::cout << "Icon hasn't been found!\n";
		std::cout << "Do you want to download it [y (requires wget) /n]? : " << std::endl;

		std::string yn;
		std::cin >> yn;

		if (yn == "y")
		{
			system("wget https://raw.githubusercontent.com/ringwormGO-organization/Termi/main/Termi-OpenGL/termi.png");

			if (!std::filesystem::exists(icon_path) || !std::filesystem::is_regular_file(icon_path))
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
	GLFWwindow *window = glfwCreateWindow(settings.GetWidth(), settings.GetHeight(), "Termi (OpenGL)", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	if (window == NULL)
	{
		std::cout << "Unable to create OpenGL window!\nExiting...\n";
		return;
	}

	else
	{
		std::cout << "OpenGL window has been created.\n";
	}

	if (iconReady)
	{
		GLFWimage images[1];
		images[0].pixels = stbi_load(icon_path.c_str(), &images[0].width, &images[0].height, 0, 4); /* rgba channels */
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

	SetFont(settings, io);

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

		/* Renders the Dear ImGui elements */
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}
