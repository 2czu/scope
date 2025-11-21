/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 10:39:52 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/21 15:42:50 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Shader.hpp"

Shader::Shader(const std::string& shaderPath, GLenum shaderType): path(shaderPath), type(shaderType), id(0)
{

}

Shader::~Shader()
{
	
}

static bool readFile(const char* pFileName, std::string &outfile)
{
    std::ifstream f(pFileName, std::ios::binary);
    if (!f.is_open())
    {
        std::cerr << "Couldn't open " << pFileName << ".\n";
        return false;
    }

    std::ostringstream ss;
    ss << f.rdbuf();
    outfile = ss.str();
    f.close();

    if (outfile.size() >= 3 &&
        (unsigned char)outfile[0] == 0xEF &&
        (unsigned char)outfile[1] == 0xBB &&
        (unsigned char)outfile[2] == 0xBF)
    {
        outfile.erase(0, 3);
    }

    return true;
}

unsigned int Shader::compile(void)
{
	std::string code;
	std::ifstream shaderFile(path);
	if (!shaderFile.is_open())
	{
		std::cerr << "Failed to open shader file: " << path << std::endl;
		return (0);
	}

	if (!readFile(path.c_str(), code))
		return (0);

	const GLchar* shaderCode = code.c_str();

	this->id = glCreateShader(type);
	if (!this->id)
		return (0);

	glShaderSource(this->id, 1, &shaderCode, nullptr);

	glCompileShader(this->id);

	GLint success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        GLchar infoLog[1024];
        glGetShaderInfoLog(id, 1024, NULL, infoLog);
        std::cerr << "Error compiling shader type : " << type << ", " << infoLog <<  "\n";
        exit(1);
    }
	return (this->id);
}

unsigned int Shader::getID() const
{
	return (this->id);
}

GLenum Shader::getType() const
{
	return (this->type);
}

std::string &Shader::getPath()
{
	return (this->path);
}