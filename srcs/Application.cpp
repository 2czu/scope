/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Application.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:31:40 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/21 19:02:15 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Application.hpp"

Application::Application()
{
    windowWidth = 1280;
    windowHeight = 720;
}

Application::~Application()
{
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

    Camera *camera = new Camera(windowWidth, windowHeight);

    scene.setCamera(camera);
}

void	Application::run(void)
{
	bool running = true;
    SDL_Event event;

	try
	{
        this->initialize();

        scene.addObject(Object3D("./resources/42.obj"));
		while (running)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
					running = false;
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