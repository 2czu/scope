/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:52:02 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/21 18:19:15 by pacda-si         ###   ########.fr       */
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
		Mesh(std::vector<float> &vertices, std::vector<unsigned int> &indices, unsigned int indexCount);
		Mesh() {};
		~Mesh() {};
		
		GLuint VAO, VBO, EBO;

		unsigned int indexCount;

		void draw();
		void print(std::vector<float> &vertices, std::vector<unsigned int> &indices);
};