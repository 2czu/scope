/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:13:04 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/22 17:12:25 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Parser.hpp"

static bool isFloat(std::string& value)
{
	std::istringstream iss(value);
	float f;
	char c;
	if (!(iss >> f))
		return false;
	if (iss >> c)
		return false;
	return true;
}

float randomFloat()
{
    return (float)(rand()) / (float)(RAND_MAX);
}

void centerModel(std::vector<Vector3f> &vertices)
{
	Vector3f min(+FLT_MAX, +FLT_MAX, +FLT_MAX);
	Vector3f max(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	for (auto& v : vertices)
	{
		if (v.x < min.x) min.x = v.x;
		if (v.y < min.y) min.y = v.y;
		if (v.z < min.z) min.z = v.z;

		if (v.x > max.x) max.x = v.x;
		if (v.y > max.y) max.y = v.y;
		if (v.z > max.z) max.z = v.z;
	}

	Vector3f center = (min + max) * 0.5f;

	for (auto& v : vertices)
	{
		v -= center;
	}
}

Mesh Parser::parseObjFile(const std::string &filepath)
{
	std::vector<Vector3f>		vertices;
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
			std::string x, y, z;
			iss >> x >> y >> z;
			iss >> std::ws;
			if (!iss.eof() || isFloat(x) == false || isFloat(y) == false || isFloat(z) == false)
				throw std::runtime_error("Wrong vertices line format");
			vertices.push_back(Vector3f(std::stof(x), std::stof(y), std::stof(z)));
			// float rf = randomFloat();
			// vertices.push_back(Vector3f(rf, rf, rf));
			vCount++;
		}
		else if (prefix == "f")
		{
			unsigned int i1, i2, i3, i4 = 0;
			if (!(iss >> i1) || !(iss >> i2) || !(iss >> i3))
				throw std::runtime_error("Wrong faces/indices line format");
			iss >> std::ws;
			if (!iss.eof() && !(iss >> i4))
				throw std::runtime_error("Wrong faces/indices line format");
			iss >> std::ws;
			if (!iss.eof())
				throw std::runtime_error("Wrong faces/indices line format");
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

	centerModel(vertices);
	Mesh mesh(vertices, indices, iCount);
	return mesh;
}