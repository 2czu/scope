/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:52:02 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/03 17:17:05 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <iostream>
#include <fstream>

#include "Math.hpp"
#include "Material.hpp"
#include "../third_party/glad/glad.h"

struct subMesh
{
    Material*					material;
    std::vector<unsigned int>	indices;
	GLuint						EBO;
};

class Mesh
{	
	public :
		Mesh(std::vector<Vertex> &vertices);
		Mesh() {};
		~Mesh() {};
		
		GLuint					VAO, VBO;
		std::vector<subMesh>	submeshes;
		std::vector<Vertex>		vertices;
		Texture					*texture;
		ShaderProgram			*shader;

		void draw();
};