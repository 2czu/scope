/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:24:17 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/12 10:26:38 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Scene.hpp"
#include "../third_party/imgui/imgui.h"
#include "../third_party/imgui/imgui_impl_sdl2.h"
#include "../third_party/imgui/imgui_impl_opengl3.h"
#include "../third_party/glad/glad.h"

class Renderer
{
	public :
		Renderer() { applyTexture = 0; displayFPS = 60;};
		~Renderer() {};
	
		int		applyTexture;
		double	displayFPS;
		double	frame_time;

		void	renderScene(Scene &scene);
		void	renderImGui(Scene &scene);
};