/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:52:02 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/22 18:22:06 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <iostream>
#include <fstream>

#include "Math.hpp"
#include "glad/glad.h"

class Mesh
{	
	public :
		Mesh(std::vector<Vector3f> &vertices, std::vector<unsigned int> &indices, unsigned int indexCount);
		Mesh() {};
		~Mesh() {};
		
		GLuint VAO, VBO, EBO;

		unsigned int indexedVertices;

		void draw();
};