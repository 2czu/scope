/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object3D.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:00:12 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/24 13:41:34 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Object3D.hpp"

Object3D::Object3D(const std::string &filepath, const std::string &shader, const std::string &texture) : material(shader, texture)
{
	mesh = Parser::parseObjFile(filepath);
	
}