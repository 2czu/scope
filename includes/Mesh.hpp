/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:52:02 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/20 19:01:35 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <iostream>
#include <fstream>

#include "Vector3f.hpp"
#include "glad/glad.h"

class Mesh
{	
	public :
		Mesh(std::vector<Vector3f> &vertices, std::vector<uint32_t> &indices);
		~Mesh() {};
		
		GLuint VAO, VBO, EBO;

		void draw();
};