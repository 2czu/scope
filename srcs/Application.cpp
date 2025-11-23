/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Application.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:31:40 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/23 17:42:58 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Application.hpp"

Application::Application()
{
    windowWidth = 1920;
    windowHeight = 1080;
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

	SDL_ShowCursor(SDL_DISABLE);
	SDL_WarpMouseInWindow(window, windowWidth / 2, windowHeight / 2);

	auto camera = std::make_unique<Camera>(windowWidth, windowHeight);

    scene.setCamera(std::move(camera));
}

void    Application::handleKeys(bool *KEYS, bool &running)
{
	float camSpeed = 0.05f;

	if (KEYS[SDLK_w])
		this->scene.camera->position += (this->scene.camera->front * camSpeed);
	if (KEYS[SDLK_s])
		this->scene.camera->position -= (this->scene.camera->front * camSpeed);
	if (KEYS[SDLK_a])
		this->scene.camera->position -= (this->scene.camera->front.cross(this->scene.camera->up)).normalized() * camSpeed;
	if (KEYS[SDLK_d])
		this->scene.camera->position += (this->scene.camera->front.cross(this->scene.camera->up)).normalized() * camSpeed;
    if (KEYS[SDLK_ESCAPE])
		running = false;
}

void	Application::run(void)
{
	bool running = true;
    SDL_Event event;
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	int x, y;
	double frame_time = 0;

    bool KEYS[322];
    
    for(int i = 0; i < 322; i++) {
        KEYS[i] = false;
    }

	try
	{
        this->initialize();

        scene.addObject(Object3D("./assets/objs/42.obj"));
		while (running)
		{
			LAST = NOW;
			NOW = SDL_GetPerformanceCounter();

			double delta_ms = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
			frame_time = delta_ms / 1000.0;

			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
					running = false;
                else if (event.type == SDL_KEYDOWN)
                {
					if (event.key.keysym.sym < 322)
                    	KEYS[event.key.keysym.sym] = true;
                }
                else if (event.type == SDL_KEYUP)
                {
					if (event.key.keysym.sym < 322)
                    	KEYS[event.key.keysym.sym] = false;
                }
				else if (event.type == SDL_MOUSEMOTION)
				{
					SDL_GetMouseState(&x, &y);
					if (x != (windowWidth / 2) || y != (windowHeight / 2))
						SDL_WarpMouseInWindow(window, windowWidth / 2, windowHeight / 2);
				}
			}


            handleKeys(KEYS, running);
			scene.camera->rotateCamera(x, y, windowWidth, windowHeight, frame_time);

			renderer.renderScene(scene);

			SDL_GL_SwapWindow(window);
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}