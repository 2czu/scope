/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Transform.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:46:45 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/23 16:55:02 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Transform.hpp"

Matrix4f Transform::getMatrix()
{
	Matrix4f m;
	return m.rotationAxis(Vector3f(0.0f, 1.0f, 0.0f), (float)(SDL_GetTicks() / 1000.0f) * (M_PI / 6));
}