/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Application.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:31:40 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/22 18:49:44 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Application.hpp"

Application::Application() : eventHandler(this)
{
    windowWidth = 1280;
    windowHeight = 720;
	running = true;
}

Application::~Application()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	if (window)
        SDL_DestroyWindow(window);
    if (glContext)
        SDL_GL_DeleteContext(glContext);
    SDL_Quit();
}

void	Application::initSDL2(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		throw std::runtime_error("");
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

    window = SDL_CreateWindow(
        "Salut", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        windowWidth, windowHeight, 
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );

    if (!window) {
        throw std::runtime_error("SDL_CreateWindow Error: ");
    }

	SDL_WarpMouseInWindow(window, windowWidth / 2, windowHeight / 2);
	SDL_GL_SetSwapInterval(0); // turns V-SYNC OFF
}

void	Application::initOpenGL(void)
{
    glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        throw std::runtime_error("SDL_GL_CreateContext Error: ");
    }

	// Loading all OpenGL functions based on the version
    if (!gladLoadGL()) {
        throw std::runtime_error("Failed to initialize GLAD");
    }

	// OpenGL configuration
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
}

void	Application::initImGui(void)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForOpenGL(window, glContext);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void	Application::initialize(void)
{
	initSDL2();
	initOpenGL();
	initImGui();

	auto camera = std::make_unique<Camera>(windowWidth, windowHeight);
    scene.setCamera(std::move(camera));

	auto light = std::make_unique<LightSource>("sphere.obj", "basic");
	scene.setLight(std::move(light));

	std::shared_ptr<Object3D> obj = scene.createObject("teapot2.obj", "phong", "brick.bmp");
    scene.addObject(obj);
}

// This gets the epoch with SDL_GetPerformanceCounter() which lets us get the time between calls
// (useful for frame time based movement speed, and fps displaying)
static double	getFrameTime(void)
{
	static Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST;

	LAST = NOW;
	NOW = SDL_GetPerformanceCounter();

	double delta_ms = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
	return (delta_ms / 1000.0);
}

void	Application::run(void)
{
	double time_wasted = 0;

	try
	{
        this->initialize();

		while (running)
		{
			renderer.frame_time = getFrameTime();
			
			time_wasted += renderer.frame_time;
			if (time_wasted >= 0.2)
			{
				renderer.displayFPS = 1.0 / renderer.frame_time;
				time_wasted = 0.0;
			}

			eventHandler.pollEvents();
			eventHandler.keysHandler();
	
			if (eventHandler.move_mouse)
			{
				scene.camera->rotateCamera(eventHandler.mouse_x, eventHandler.mouse_y,
					windowWidth, windowHeight, renderer.frame_time);	
			}

			renderer.renderScene(scene);
			renderer.renderImGui(scene);

			SDL_GL_SwapWindow(window);
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}