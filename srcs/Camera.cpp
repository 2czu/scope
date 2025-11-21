/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:20:58 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/21 18:45:21 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Camera.hpp"


Camera::Camera(int windowWidth, int windowHeight)
{
	position = Vector3f(0.0f, 0.0f, -10.0f);
	FOV = M_PI / 4;
	near_plane = 0.1f;
	far_plane = 100.0f;
	aspect_ratio = (float)windowWidth / (float)windowHeight;
}

Matrix4f Camera::getViewMatrix()
{
	Matrix4f m;
	return m.translation(position);
}

Matrix4f Camera::getProjMatrix()
{
	Matrix4f m;
	return m.perspective(FOV, aspect_ratio, near_plane, far_plane);
}