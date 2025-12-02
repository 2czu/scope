/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventHandler.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:13:36 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/02 20:12:15 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Application.hpp"

EventHandler::EventHandler(Application *application) 
{
	this->app = application;
	for(int i = 0; i < 322; i++)
		KEYS[i] = false;
	lmb_down = false;
	mouse_x = 0;
	mouse_y = 0;
	move_mouse = false;
};

void	EventHandler::mouseHandler()
{
	SDL_GetMouseState(&mouse_x, &mouse_y);
	// if ((mouse_moved == false) && ((mouse_x != (*app).windowWidth / 2) || (mouse_y != (*app).windowHeight / 2)))
	// 	mouse_moved = true;
	// else
	// 	mouse_moved = false;
}

void	EventHandler::keysHandler()
{
	const float camSpeed = 0.05f;

	if (KEYS[SDLK_w])
		(*app).scene.camera->position += ((*app).scene.camera->front * camSpeed);
	if (KEYS[SDLK_s])
		(*app).scene.camera->position -= ((*app).scene.camera->front * camSpeed);
	if (KEYS[SDLK_a])
		(*app).scene.camera->position -= ((*app).scene.camera->front.cross((*app).scene.camera->up)).normalized() * camSpeed;
	if (KEYS[SDLK_d])
		(*app).scene.camera->position += ((*app).scene.camera->front.cross((*app).scene.camera->up)).normalized() * camSpeed;
	if (KEYS[SDLK_ESCAPE])
		(*app).running = false;
	if (KEYS[SDLK_v])
	{
		move_mouse = true;
		SDL_ShowCursor(SDL_DISABLE);
	}
	if (KEYS[SDLK_b])
	{
		move_mouse = false;
		SDL_ShowCursor(SDL_ENABLE);
	}
	if (KEYS[SDLK_i])
		(*app).scene.light->position.y += 0.1f;
	if (KEYS[SDLK_k])
		(*app).scene.light->position.y -= 0.1f;
	if (KEYS[SDLK_j])
		(*app).scene.light->position.x += 0.1f;
	if (KEYS[SDLK_l])
		(*app).scene.light->position.x -= 0.1f;
}

void	EventHandler::pollEvents()
{
	while ((*app).running && SDL_PollEvent(&event))
	{
		ImGui_ImplSDL2_ProcessEvent(&event);
		if (event.type == SDL_QUIT)
			(*app).running = false;
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
			if (move_mouse)
			{
				SDL_GetMouseState(&mouse_x, &mouse_y);
				mouse_x -= (*app).windowWidth / 2;
				mouse_y -= (*app).windowHeight / 2;
				SDL_WarpMouseInWindow((*app).window, (*app).windowWidth / 2, (*app).windowHeight / 2);	
			}
			else
			{
				mouse_x = 0;
				mouse_y = 0;
			}
				
		}
		// else if (event.type == SDL_MOUSEBUTTONUP)
		// {
		// 	lmb_down = false;
		// 	SDL_ShowCursor(SDL_DISABLE);
		// }
		// else if (event.type == SDL_MOUSEBUTTONDOWN)
		// {
		// 	lmb_down = true;
		// 	SDL_ShowCursor(SDL_ENABLE);
		// }
	}
}