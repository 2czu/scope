/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:45:58 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/21 20:37:44 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Mesh.hpp"

Mesh::Mesh(std::vector<float> &vertices, std::vector<unsigned int> &indices, unsigned int indexCount)
{
    this->indexedVertices = indexCount * 3;

	glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    // glEnableVertexAttribArray(2);
}

void Mesh::draw(void)
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, this->indexedVertices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::print(std::vector<float> &vertices, std::vector<unsigned int> &indices)
{
    int count = 0;
    for (float &f : vertices)
    {
        std::cout << f << ", ";
        count++;
        if(count == 3)
        {
            std::cout << "\n";
            count = 0;
        }
    }
    for (unsigned int &i : indices)
    {
        std::cout << i << " ";
        count++;
        if(count == 3)
        {
            std::cout << "\n";
            count = 0;
        }
    }
}