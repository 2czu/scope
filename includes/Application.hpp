/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Application.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:29:58 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/23 17:40:30 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include "../third_party/glad/glad.h"
#include "../third_party/KHR/khrplatform.h"
#include "Renderer.hpp"
#include "Scene.hpp"
#include <algorithm>
#include <memory>

class Application
{
	public :
		Application();
		~Application();

		SDL_Window		*window;
		int				windowWidth;
		int				windowHeight;
		SDL_GLContext	glContext;

		Scene			scene;
		Renderer		renderer;

		void			initialize();
		void			run();
		void			handleKeys(bool *KEYS, bool &running);

};