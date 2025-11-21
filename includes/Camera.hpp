/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 12:56:26 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/21 17:43:12 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Matrix4f.hpp"
#include "Vector3f.hpp"

class Camera
{
	public :
		Camera(int windowWidth, int windowHeight);
		~Camera() {};

		Vector3f		position;
		float			FOV;
		float			near_plane;
		float			far_plane;
		float			aspect_ratio;
		
		Matrix4f getViewMatrix();
		Matrix4f getProjMatrix();
};