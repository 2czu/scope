/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:24:17 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/25 20:25:05 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Scene.hpp"
#include "../third_party/imgui/imgui.h"
#include "../third_party/imgui/imgui_impl_sdl2.h"
#include "../third_party/imgui/imgui_impl_opengl3.h"

class Renderer
{
	public :
		Renderer() {};
		~Renderer() {};
	
		void	renderScene(Scene &scene);
};