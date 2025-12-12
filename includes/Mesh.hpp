/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:52:02 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/12 17:18:35 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <memory>

#include "Math.hpp"
#include "Material.hpp"
#include "../third_party/glad/glad.h"

struct subMesh
{
    Material*					material;
    std::vector<unsigned int>	indices;
	GLuint						EBO;

	subMesh() {material = nullptr;};
};

class Mesh
{	
	public :
		Mesh(std::vector<Vertex> &vertices, std::vector<subMesh> &submeshes);
		Mesh(const Mesh &other);
		Mesh &operator=(const Mesh &other);
		Mesh() { texture = NULL; };
		~Mesh();
		
		GLuint							VAO, VBO;
		std::vector<subMesh>			submeshes;
		std::vector<Vertex>				vertices;
		ShaderProgram					*shader;
		Texture							*texture;

		void	draw();
};