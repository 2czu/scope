/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LightSource.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:15:59 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/22 18:52:01 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/LightSource.hpp"

LightSource::LightSource(std::string meshpath, std::string shaderf) : shader("./assets/shaders/" + shaderf),
																	mesh(Parser::loadMesh("./assets/objs/" + meshpath))
{
	mesh.shader = &shader;
	color = Vector3f(1.0f, 1.0f, 1.0f);
	position = Vector3f(-2.5f, 1.0f, 2.5f);
}