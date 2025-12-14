/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:13:04 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/14 18:40:35 by pacda-si         ###   ########.fr       */
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

static void clearMaterialList(std::unordered_map<std::string, Material *> &materials)
{
    for (auto &p : materials)
    {
        if (p.second)
            delete(p.second);
    }
    materials.clear();
}

static void setRemainingMaterial(std::vector<subMesh> &submeshes)
{
    for (auto &p : submeshes)
    {
        if (p.material == nullptr)
            p.material = new Material();
    }
}

static void loadMaterialList(std::istringstream &iss, std::unordered_map<std::string, Material *> &mats)
{
	std::string					line;
	Material					*current = NULL;
    std::string                 mtlFile;
    std::string                 filepath;

    iss >> mtlFile;
    filepath = "./assets/mats/" + mtlFile;

    std::ifstream				ifs(filepath);
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
				mat->name = mtl;
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
				loadType<int>(iss, current->illum);
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


void    handlePositionVertex(std::istringstream &iss, std::vector<Vertex> &vertices)
{
    Vector3f pos;
    if (!(iss >> pos.x >> pos.y >> pos.z))
        throw std::runtime_error("Bad vertex line");

    iss >> std::ws;
    if (!iss.eof())
        throw std::runtime_error("Bad vertex line");

    // float rf = clamp(randomFloat(), 0.1f, 0.9f);

    Vertex v;
    v.position = pos;
    v.color = Vector3f(1, 1, 1);
    v.uv = Vector2f(pos.x, pos.y).normalized();

    vertices.push_back(v);
}

void setMaterial(std::istringstream &iss,
                    std::unordered_map<std::string, Material*>  &materials,
                    std::vector<subMesh> &submeshes,
                    subMesh** currentSubmesh
                )
{
    std::string mname;
    iss >> mname;

    Material* mat = nullptr;
    if (materials.count(mname))
        mat = materials[mname];

    bool found = false;
    for (auto &s : submeshes)
    {
        if (s.material == mat)
        {
            *currentSubmesh = &s;
            found = true;
            break;
        }
    }

    if (!found)
    {
        subMesh newS;
        if (mat != nullptr)
            newS.material = mat->clone();
        submeshes.push_back(newS);
        *currentSubmesh = &submeshes.back();
    }
}

void handleFace(std::istringstream &iss,
                    std::vector<unsigned int> &globalIndices,
                    std::vector<subMesh> &submeshes,
                    subMesh **currentSubmesh, size_t size)
{
    if (!*currentSubmesh)
    {
        subMesh def;
        def.material = nullptr;
        submeshes.push_back(def);
        *currentSubmesh = &submeshes.back();
    }

    unsigned int i1 = 0, i2 = 0, i3 = 0, i4 = 0;
    if (!(iss >> i1 >> i2 >> i3) || (i1 == 0 || i1 > size) 
        || (i2 == 0 || i2 > size) 
        || (i3 == 0 || i3 > size))
        throw std::runtime_error("Bad face line");

    iss >> std::ws;
    if (!iss.eof() && (!(iss >> i4) || i4 == 0 || i4 > size))
        throw std::runtime_error("Bad fourth face argument");

    (*currentSubmesh)->indices.push_back(i1 - 1);
    (*currentSubmesh)->indices.push_back(i2 - 1);
    (*currentSubmesh)->indices.push_back(i3 - 1);

    globalIndices.push_back(i1 - 1);
    globalIndices.push_back(i2 - 1);
    globalIndices.push_back(i3 - 1);

    if (i4 != 0)
    {
        (*currentSubmesh)->indices.push_back(i1 - 1);
        (*currentSubmesh)->indices.push_back(i3 - 1);
        (*currentSubmesh)->indices.push_back(i4 - 1);

        globalIndices.push_back(i1 - 1);
        globalIndices.push_back(i3 - 1);
        globalIndices.push_back(i4 - 1);
    }
}

Mesh Parser::loadMesh(const std::string &filepath)
{
    // std::vector<Vector3f>                       positions;
    // std::vector<Vector2f>                       uvs;
    // std::vector<Vector3f>                       normals;
    std::vector<Vertex>                         vertices;
    std::vector<unsigned int>                   globalIndices;
    std::unordered_map<std::string, Material*>  materials;

    std::vector<subMesh>                        submeshes;
    subMesh*                                    currentSubmesh = nullptr;

    std::ifstream ifs(filepath);
    if (!ifs.is_open())
        throw std::runtime_error("File not found");

    std::string line;
    srand(time(NULL));

    try
    {
        while (std::getline(ifs, line))
        {
            std::istringstream iss(line);
            std::string token;
            iss >> token;

            if (token == "v")
                handlePositionVertex(iss, vertices);
            else if (token == "mtllib")
                loadMaterialList(iss, materials);
            else if (token == "usemtl")
                setMaterial(iss, materials, submeshes, &currentSubmesh);
            else if (token == "f")
                handleFace(iss, globalIndices, submeshes, &currentSubmesh, vertices.size());
        }
        setRemainingMaterial(submeshes);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        clearMaterialList(materials);
        throw std::runtime_error("");
    }

    clearMaterialList(materials);
    centerModel(vertices);
    computeVertexNormals(vertices, globalIndices);

    Mesh mesh(vertices, submeshes);
    return mesh;
}