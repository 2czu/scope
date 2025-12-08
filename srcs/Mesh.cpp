/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:45:58 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/08 12:14:13 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Mesh.hpp"

// unsigned int loadCubemap(std::vector<std::string> faces)
// {
// 	unsigned int textureID;
// 	glGenTextures(1, &textureID);
// 	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

// 	int width, height, nrChannels;
// 	for (unsigned int i = 0; i < faces.size(); i++)
// 	{
// 		unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
// 		if (data)
// 		{
// 			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
// 						0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
// 			);
// 			stbi_image_free(data);
// 		}
// 		else
// 		{
// 			std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
// 			stbi_image_free(data);
// 		}
// 	}
// 	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// 	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
// 	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
// 	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

// 	return textureID;
// }

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<subMesh> &submeshes) : texture(NULL)
{
	// std::vector<std::string> faces
	// {
	// 	"./skyy/right.png",
	// 	"./skyy/left.png",
	// 	"./skyy/top.png",
	// 	"./skyy/bottom.png",
	// 	"./skyy/front.png",
	// 	"./skyy/back.png"
	// };

	// unsigned int cubemapTexture = loadCubemap(faces);

	glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, norm));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
    glEnableVertexAttribArray(3);

    this->submeshes = submeshes;

    for(auto &sm : this->submeshes)
    {
        glGenBuffers(1, &sm.EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sm.EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sm.indices.size() * sizeof(unsigned int),
            sm.indices.data(), GL_STATIC_DRAW);
    }

}

Mesh::Mesh(const Mesh &other)
{
    this->submeshes = other.submeshes;
    this->VAO = other.VAO;
    this->VBO = other.VBO;
    this->vertices = other.vertices;
    this->shader = other.shader;
    this->texture = other.texture;
}

Mesh &Mesh::operator=(const Mesh &other)
{
    if (this != &other)
    {
        this->submeshes = other.submeshes;
        this->VAO = other.VAO;
        this->VBO = other.VBO;
        this->vertices = other.vertices;
        this->shader = other.shader;
        this->texture = other.texture;
    }
    return (*this);
}

Mesh::~Mesh()
{
    if (texture)
        delete texture;
    for (auto &submesh : submeshes)
    {
        if (submesh.material)
            delete submesh.material;
    }
}

void Mesh::draw(void)
{

    static int x = 0;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);

    glBindVertexArray(VAO);

    if (texture)
        texture->bind();
    for(auto &sm : submeshes)
    {
        sm.material->bind(shader);
        if (x == 1)
            sm.material->print();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sm.EBO);
        glDrawElements(GL_TRIANGLES, sm.indices.size(), GL_UNSIGNED_INT, 0);
    }
    x++;
    if (texture)
        texture->unbind();
}

