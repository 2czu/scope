/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scene.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 12:50:29 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/23 17:42:30 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Object3D.hpp"
#include "Camera.hpp"
#include <memory>
#include <algorithm>

class Scene
{
	private :
	
	public :
		Scene() { camera = NULL; };
		~Scene() {};
		
		std::unique_ptr<Camera>	camera;
		std::vector<Object3D>	objs;
		void	addObject(const Object3D &obj);
		void	setCamera(std::unique_ptr<Camera> camera);
};