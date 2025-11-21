/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scene.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 12:50:29 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/21 16:58:04 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Object3D.hpp"
#include "Camera.hpp"

class Scene
{
	private :
	
	public :
		Scene() { camera = NULL; };
		~Scene() {};
		
		Camera					*camera;
		std::vector<Object3D>	objs;
		void	addObject(const Object3D &obj);
		void	setCamera(Camera *camera);
};