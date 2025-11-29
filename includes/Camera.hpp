/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 12:56:26 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/27 10:44:53 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Math.hpp"

class Camera
{
	public :
		Camera(int windowWidth, int windowHeight);
		~Camera() {};

		Vector3f		position;
		Vector3f		target;
		Vector3f		direction;
		Vector3f		right;
		Vector3f		up;
		Vector3f		front;

		float			FOV;
		float			near_plane;
		float			far_plane;
		float			aspect_ratio;
		float			pitch;
		float			yaw;
		
		Matrix4f getViewMatrix();
		Matrix4f getProjMatrix();

		void	 rotateCamera(const int &x, const int &y, const int &windowWidth,
								const int &windowHeight, const float &frame_time);
};