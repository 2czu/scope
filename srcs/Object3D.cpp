/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object3D.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:00:12 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/29 18:42:55 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Object3D.hpp"

Object3D::Object3D(const std::string &meshpath, const std::string &shaderf, 
	const std::string &matpath, const std::string &texture) : shader(shaderf), material(NULL)
{
	(void)texture;
	mesh = Parser::loadMesh(meshpath);
	material = Parser::loadMaterial(matpath);

}