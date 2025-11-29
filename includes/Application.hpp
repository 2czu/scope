/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Application.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:29:58 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/29 18:23:00 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include "../third_party/glad/glad.h"
#include "../third_party/KHR/khrplatform.h"
#include "../third_party/imgui/imgui.h"
#include "../third_party/imgui/imgui_impl_sdl2.h"
#include "../third_party/imgui/imgui_impl_opengl3.h"
// #include "../third_party/imgui/imgui_impl_opengl3_loader.h"
#include "Renderer.hpp"
#include "Scene.hpp"
#include "LightSource.hpp"
#include <algorithm>
#include <memory>
#define	SC_NONE ""

class Application;

struct	EventHandler
{
	EventHandler(Application *application);
	~EventHandler() {};

	SDL_Event	event;
	Application	*app;
	bool		KEYS[322];
	int			mouse_x;
	int			mouse_y;
	bool		lmb_down;
	bool		move_mouse;

	void	mouseHandler();
	void	keysHandler();
	void	pollEvents();
};

class Application
{
	public :
		Application();
		~Application();

		SDL_Window		*window;
		SDL_GLContext	glContext;
		int				windowWidth;
		int				windowHeight;

		Scene			scene;
		Renderer		renderer;
		EventHandler	eventHandler;

		bool			running;

		void			initialize();
		void			run();

};