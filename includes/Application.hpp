/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Application.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:29:58 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/20 18:39:38 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <glad/glad.h>
#include <KHR/khrplatform.h>
#include "Renderer.hpp"

class Application
{
	public :
		Application();
		~Application();

		SDL_Window		*window;
		int				windowWidth;
		int				windowHeight;
		SDL_GLContext	glContext;

		Renderer		renderer;

		int				initialize();
		void			run();

};