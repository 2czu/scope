/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:13:04 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/03 17:00:39 by pacda-si         ###   ########.fr       */
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

void loadMaterials(std::unordered_map<std::string, Material *> &mats, const std::string &filepath)
{
	std::ifstream				ifs(filepath);
	std::string					line;
	Material					*current = NULL;

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
			if (mats.find(mtl) == mats.end())
			{
				Material	*mat = new Material();
				mats[mtl] = mat;
			}
			current = mats[mtl];
		}
		if (current)
		{
			if (prefix == "Ns")
				loadType<float>(iss, current->ns);
			else if (prefix == "Ka")
				loadVec3(iss, current->ka);
			else if (prefix == "Kd")
				loadVec3(iss, current->kd);
			else if (prefix == "Ks")
				loadVec3(iss, current->ks);
			else if (prefix == "d")
				loadType<float>(iss, current->d);
			else if (prefix == "illum")
				loadType<float>(iss, current->illum);
		}
	}

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
	std::vector<Vertex>							vertices;
	std::vector<unsigned int>					indices;
	std::unordered_map<std::string, Material *> materials;
	std::unordered_map<Material *, subMesh>		matToSubmesh;
	std::vector<subMesh>						submeshes;		
	Material*									currentMat;
	subMesh*									currentSubmesh;

	std::ifstream			ifs(filepath);
	std::string				line;
	unsigned int			vCount = 0;
	unsigned int			iCount = 0;
	
	loadMaterials(materials, filepath);

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
				currentSubmesh->indices.push_back(i1 - 1);
				currentSubmesh->indices.push_back(i2 - 1);
				currentSubmesh->indices.push_back(i3 - 1);
				indices.push_back(i1 - 1);
				indices.push_back(i2 - 1);
				indices.push_back(i3 - 1);
				iCount++;
				if (i4)
				{
					currentSubmesh->indices.push_back(i1 - 1);
					currentSubmesh->indices.push_back(i3 - 1);
					currentSubmesh->indices.push_back(i4 - 1);
					indices.push_back(i1 - 1);
					indices.push_back(i3 - 1);
					indices.push_back(i4 - 1);
					iCount++;
				}

			}
		}
		else if (prefix == "usemtl")
		{
			std::string mtl;
			if (!(iss >> mtl))
				throw std::runtime_error("Wrong material name format");
			Material *toSearch;
			if (materials.find(mtl) != materials.end())
			{
				toSearch = materials[mtl];
				if (matToSubmesh.find(toSearch) == matToSubmesh.end())
				{
					subMesh newsubMesh;
					newsubMesh.material = toSearch;
					matToSubmesh[toSearch] = newsubMesh;
					submeshes.push_back(newsubMesh);
				}
				currentSubmesh = &matToSubmesh[toSearch];
			}
		}
	}

	centerModel(vertices);
	computeVertexNormals(vertices, indices);
	Mesh mesh;
	mesh.submeshes = submeshes;
	mesh.vertices = vertices;
	return mesh;
}