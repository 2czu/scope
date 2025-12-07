/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scene.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 12:54:41 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/06 15:30:07 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Scene.hpp"

void	Scene::addObject(std::shared_ptr<Object3D> obj)
{
	this->objs.push_back(obj);	
}

std::shared_ptr<Object3D>	Scene::createObject(std::string objfile, std::string shaderfile, std::string texture)
{
	objfile = "./assets/objs/" + objfile;
	shaderfile = "./assets/shaders/" + shaderfile;
	texture = "./assets/textures/" + texture;
	return (std::make_shared<Object3D>(objfile, shaderfile, texture));	
}


void	Scene::setCamera(std::unique_ptr<Camera> camera)
{
	this->camera = std::move(camera);
}

void	Scene::setLight(std::unique_ptr<LightSource> light)
{
	this->light = std::move(light);
}