/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object3D.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:00:12 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/03 17:14:11 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Object3D.hpp"

Object3D::Object3D(const std::string &meshpath, const std::string &shaderf, 
	const std::string &matpath, const std::string &texture) : shader(shaderf)
{
	mesh = Parser::loadMesh(meshpath);
	mesh.shader = &shader;
}