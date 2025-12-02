/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:13:04 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/02 15:27:14 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Parser.hpp"
#include <unordered_map>


float randomFloat()
{
    return (float)(rand()) / (float)RAND_MAX;
}


void centerModel(std::vector<Vertex> &vertices)
{
	Vector3f min(+FLT_MAX, +FLT_MAX, +FLT_MAX);
	Vector3f max(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	for (auto& v : vertices)
	{
		if (v.position.x < min.x) min.x = v.position.x;
		if (v.position.y < min.y) min.y = v.position.y;
		if (v.position.z < min.z) min.z = v.position.z;

		if (v.position.x > max.x) max.x = v.position.x;
		if (v.position.y > max.y) max.y = v.position.y;
		if (v.position.z > max.z) max.z = v.position.z;
	}

	Vector3f center = (min + max) * 0.5f;

	for (auto& v : vertices)
	{
		v.position -= center;
	}
}

template <typename T>
static void	loadType(std::istringstream &iss, T &var)
{
	if (!(iss >> var))
		throw std::runtime_error("Wrong Vector3f line format");
	iss >> std::ws;
	if (!iss.eof())
		throw std::runtime_error("Wrong Vector3f line format");
}

static void	loadVec3(std::istringstream &iss, Vector3f &vec)
{
	if (!(iss >> vec.x >> vec.y >> vec.z))

		throw std::runtime_error("Wrong vertices line format");
	iss >> std::ws;
	if (!iss.eof())
		throw std::runtime_error("Wrong vertices line format");
}

Material *Parser::loadMaterial(const std::string &filepath)
{
	std::ifstream				ifs(filepath);
	std::string					line;

	Material	*mat = new Material();

	if (!ifs.is_open())
		throw std::runtime_error("File not found");
	while (std::getline(ifs, line))
	{
		std::istringstream	iss(line);
		std::string			prefix;

		iss >> prefix;
		
		if (prefix == "newmtl")
		{
			std::string mtl;
			if (!(iss >> mtl))
				throw std::runtime_error("Wrong material name format");
			mat->name = mtl;
			
		}
		else if (prefix == "Ns")
			loadType<float>(iss, mat->ns);
		else if (prefix == "Ka")
			loadVec3(iss, mat->ka);
		else if (prefix == "Kd")
			loadVec3(iss, mat->kd);
		else if (prefix == "Ks")
			loadVec3(iss, mat->ks);
		else if (prefix == "d")
			loadType<float>(iss, mat->d);
		else if (prefix == "illum")
			loadType<float>(iss, mat->illum);
	}

	mat->print();

	return (mat);

}


static void computeVertexNormals(
    std::vector<Vertex>& vertices,
    const std::vector<unsigned int>& indices)
{
    for (size_t i = 0; i < indices.size(); i += 3)
    {
        unsigned int i0 = indices[i];
        unsigned int i1 = indices[i + 1];
        unsigned int i2 = indices[i + 2];

        const Vector3f& v0 = vertices[i0].position;
        const Vector3f& v1 = vertices[i1].position;
        const Vector3f& v2 = vertices[i2].position;

        Vector3f e1 = v1 - v0;
        Vector3f e2 = v2 - v0;

        Vector3f faceNormal = e1.cross(e2);

        vertices[i0].norm += faceNormal;
        vertices[i1].norm += faceNormal;
        vertices[i2].norm += faceNormal;
    }

    for (Vertex& v : vertices)
        v.norm = v.norm.normalized();
}


Mesh Parser::loadMesh(const std::string &filepath)
{
	std::vector<Vertex>			vertices;
	std::vector<unsigned int>	indices;
	std::ifstream			ifs(filepath);
	std::string				line;
	unsigned int			vCount = 0;
	unsigned int			iCount = 0;
	
	srand(time(NULL));

	if (!ifs.is_open())
		throw std::runtime_error("File not found");
	while (std::getline(ifs, line))
	{
		std::istringstream	iss(line);
		std::string			prefix;

		iss >> prefix;
		
		if (prefix == "v")
		{
			Vector3f pos;
			if (!(iss >> pos.x >> pos.y >> pos.z))
				throw std::runtime_error("Wrong vertices line format");
			iss >> std::ws;
			if (!iss.eof())
				throw std::runtime_error("Wrong vertices line format");

			Vertex new_vertex;
			// float rf = clamp(randomFloat(), 0.1f, 0.9f);

			new_vertex.position = pos;
			new_vertex.color = Vector3f(1.0f, 1.0f, 1.0f);
			new_vertex.uv = Vector2f(new_vertex.position.x, new_vertex.position.y).normalized();
			
			vertices.push_back(new_vertex);
			vCount++;
		}
		else if (prefix == "f")
		{
			unsigned int i1, i2, i3, i4 = 0;
			if (!(iss >> i1) || !(iss >> i2) || !(iss >> i3))
				throw std::runtime_error("Wrong faces/indices line format");
			iss >> std::ws;
			iss >> i4;
			if (i1 && i2 && i3)
			{
				indices.push_back(i1 - 1);
				indices.push_back(i2 - 1);
				indices.push_back(i3 - 1);
				iCount++;
				if (i4)
				{
					indices.push_back(i1 - 1);
					indices.push_back(i3 - 1);
					indices.push_back(i4 - 1);
					iCount++;
				}

			}
		}
	}
	
	// int i = 0;

	// std::vector<float>::iterator it1 = vertices.begin();	
	// std::vector<float>::iterator ite1 = vertices.end();

	// std::cout << "Vertices :\n";
	// while (it1 != ite1)
	// {
	// 	std::cout << *it1 << " ";
	// 	i++;
	// 	if (i == 6)
	// 	{
	// 		std::cout << std::endl;
	// 		i = 0;
	// 	}
	// 	it1++;
	// }

	// i = 0;

	// std::vector<unsigned int>::iterator it = indices.begin();	
	// std::vector<unsigned int>::iterator ite = indices.end();

	// std::cout << "Indices :\n";
	// while (it != ite)
	// {
	// 	std::cout << *it << " ";
	// 	i++;
	// 	if (i == 3)
	// 	{
	// 		std::cout << std::endl;
	// 		i = 0;
	// 	}
	// 	it++;
	// }

	// std::cout << "\n" << iCount << std::endl;

	// std::cout << "\n" << vCount << std::endl;

	// std::cout << "\n" << vertices.size() << std::endl;

	
	// std::vector<Vertex>::iterator it = vertices.begin();	
	// std::vector<Vertex>::iterator ite = vertices.end();
	// while (it != ite)
	// {
	// 	std::cout << (*it).uv.x << ", " << (*it).uv.y << std::endl;
	// 	it++;
	// }

	centerModel(vertices);
	computeVertexNormals(vertices, indices);
	Mesh mesh(vertices, indices, iCount);
	return mesh;
}