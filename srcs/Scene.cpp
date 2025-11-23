/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scene.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 12:54:41 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/23 17:41:54 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Scene.hpp"

void	Scene::addObject(const Object3D &obj)
{
	this->objs.push_back(obj);	
}

void	Scene::setCamera(std::unique_ptr<Camera> camera)
{
	this->camera = std::move(camera);
}
