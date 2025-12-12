/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Transform.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:43:40 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/12 16:54:18 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Math.hpp"
#include <SDL2/SDL.h>

class Transform
{
	private :
		Matrix4f m;

	public :
		Transform() {};
 		~Transform() {};

		Matrix4f getMatrix();
		void	 setMatrix(const Matrix4f &m);
};