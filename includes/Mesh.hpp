/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:52:02 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/24 15:00:48 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <iostream>
#include <fstream>

#include "Math.hpp"
#include "../third_party/glad/glad.h"

class Mesh
{	
	public :
		Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, unsigned int indexCount);
		Mesh() {};
		~Mesh() {};
		
		GLuint VAO, VBO, EBO;

		unsigned int indexedVertices;

		void draw();
};