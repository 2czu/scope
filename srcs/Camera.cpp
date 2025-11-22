/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:20:58 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/22 17:52:16 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Camera.hpp"


Camera::Camera(int windowWidth, int windowHeight)
{
	position = Vector3f(0.0f, 0.0f, 5.0f);
	front = Vector3f(0.0f, 0.0f, -1.0f);
	up = Vector3f(0.0f, 1.0f, 0.0f);
	// target = Vector3f(0.0f, 0.0f, 0.0f);
	// direction = (position - target).normalized();
	// right = glm::normalize(glm::cross(up, cameraDirection));
	pitch = 0.0f;
	yaw = -90.0f;
	FOV = 0.66;
	near_plane = 0.1f;
	far_plane = 100.0f;
	aspect_ratio = (float)windowWidth / (float)windowHeight;
}

void	 Camera::rotateCamera(const int &x, const int &y, const int &windowWidth, const int &windowHeight, const float &frame_time)
{
	static float current_speed_x = 0, current_speed_y = 0;

	float xoffset = x - (windowWidth / 2);
	float yoffset = (windowHeight / 2) - y;

	float aspect = (float)windowWidth / (float)windowHeight;
	float xnorm = xoffset / windowWidth;
	float ynorm = yoffset / (windowHeight * aspect);

	const float sensitivity = 30.0f;
	float target_speed_x = xnorm * sensitivity;
	float target_speed_y = ynorm * sensitivity;

	const float max_speed = 60.0f;
	target_speed_x = clamp(target_speed_x, -max_speed, max_speed);
	target_speed_y = clamp(target_speed_y, -max_speed, max_speed);

	const float smoothing_time = 0.1f;
	float alpha = 1.0f - expf(-frame_time / smoothing_time);

	current_speed_x += (target_speed_x - current_speed_x) * alpha;
	current_speed_y += (target_speed_y - current_speed_y) * alpha;

	this->yaw   += current_speed_x;
	this->pitch += current_speed_y;

	this->pitch = clamp(this->pitch, -89.0f, 89.0f);

	Vector3f direction;
	direction.x = cos(degToRad(this->yaw)) * cos(degToRad(this->pitch));
	direction.y = sin(degToRad(this->pitch));
	direction.z = sin(degToRad(this->yaw)) * cos(degToRad(this->pitch));
	this->front = direction.normalized();
	
}


Matrix4f Camera::getViewMatrix()
{
	Matrix4f m;
	return m.lookAt(position, position + front, up);
}

Matrix4f Camera::getProjMatrix()
{
	Matrix4f m;
	return m.perspective(FOV, aspect_ratio, near_plane, far_plane);
}