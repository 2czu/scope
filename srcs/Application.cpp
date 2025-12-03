/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Application.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:31:40 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/03 18:18:51 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Application.hpp"

Application::Application() : eventHandler(this)
{
    windowWidth = 1920;
    windowHeight = 1080;
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

void	Application::initialize(void)
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

    glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        throw std::runtime_error("SDL_GL_CreateContext Error: ");
    }

    if (!gladLoadGL()) {
        throw std::runtime_error("Failed to initialize GLAD");
    }

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForOpenGL(window, glContext);
	ImGui_ImplOpenGL3_Init("#version 330");

	SDL_WarpMouseInWindow(window, windowWidth / 2, windowHeight / 2);
	auto camera = std::make_unique<Camera>(windowWidth, windowHeight);

    scene.setCamera(std::move(camera));
}

void	Application::run(void)
{
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double frame_time = 0;


	try
	{
        this->initialize();

		auto light = std::make_unique<LightSource>("./assets/objs/cube.obj", "./assets/shaders/lightCube");
		scene.setLight(std::move(light));

		std::shared_ptr<Object3D> obj = scene.createObject("spk.obj", "shader", "matte.mtl", "brickc.png");
        scene.addObject(obj);

		while (running)
		{
			
			LAST = NOW;
			NOW = SDL_GetPerformanceCounter();

			double delta_ms = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
			frame_time = delta_ms / 1000.0;

			eventHandler.pollEvents();
			eventHandler.keysHandler();
			
			if (eventHandler.move_mouse)
			{
				scene.camera->rotateCamera(eventHandler.mouse_x, eventHandler.mouse_y,
					windowWidth, windowHeight, frame_time);	
			}
		
			renderer.renderScene(scene);

			SDL_GL_SwapWindow(window);
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}