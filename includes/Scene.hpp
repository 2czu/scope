/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scene.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 12:50:29 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/06 15:30:14 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Object3D.hpp"
#include "Camera.hpp"
#include "LightSource.hpp"
#include <memory>
#include <algorithm>

class Scene
{
	private :
	
	public :
		Scene() { camera = NULL; };
		~Scene() {};
		
		std::unique_ptr<Camera>					camera;
		std::unique_ptr<LightSource>			light;
		std::vector<std::shared_ptr<Object3D>>	objs;

		void						setCamera(std::unique_ptr<Camera> camera);
		void						setLight(std::unique_ptr<LightSource> camera);

		std::shared_ptr<Object3D>	createObject(std::string objfile, std::string shaderfile,
												std::string texture);
		void						addObject(std::shared_ptr<Object3D>);
};