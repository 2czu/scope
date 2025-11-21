/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Transform.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:43:40 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/21 17:51:39 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Matrix4f.hpp"
#include <SDL2/SDL.h>

class Transform
{
	public :
		Transform() {};
 		~Transform() {};
		
		Matrix4f getMatrix();
};