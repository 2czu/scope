/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scene.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 12:54:41 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/21 20:10:39 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Scene.hpp"

void	Scene::addObject(const Object3D &obj)
{
	this->objs.push_back(obj);	
}

void	Scene::setCamera(Camera *camera)
{
	this->camera = camera;
}
