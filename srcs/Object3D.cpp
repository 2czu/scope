/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object3D.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:00:12 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/02 18:49:43 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Object3D.hpp"

Object3D::Object3D(const std::string &meshpath, const std::string &shaderf, 
	const std::string &matpath, const std::string &texture) : shader(shaderf), material(NULL)
{
	mesh = Parser::loadMesh(meshpath);
	material = Parser::loadMaterial(matpath);
	material->texture = new Texture(texture);

}