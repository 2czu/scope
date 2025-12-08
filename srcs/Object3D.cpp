/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object3D.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:00:12 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/08 12:16:04 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Object3D.hpp"

Object3D::Object3D(const std::string &meshpath, const std::string &shaderf, const std::string &texture) : mesh(Parser::loadMesh(meshpath)), shader(shaderf)
{
	mesh.shader = &shader;
	Texture *textur = new Texture(texture);
	mesh.texture = textur;
}