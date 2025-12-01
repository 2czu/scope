/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LightSource.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:15:59 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/01 15:39:55 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/LightSource.hpp"

LightSource::LightSource(std::string meshpath, std::string shaderf) : shader(shaderf)
{
	mesh = Parser::loadMesh(meshpath);

	color = Vector3f(1.0f, 1.0f, 1.0f);
	position = Vector3f(0.0f, 1.0f, 0.0f);
}