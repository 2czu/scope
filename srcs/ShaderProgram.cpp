/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShaderProgram.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 11:43:46 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/02 18:44:01 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ShaderProgram.hpp"

ShaderProgram::ShaderProgram(const std::string &shader) : programID(0)
{
    std::string vsrc = shader + ".vs";
    std::string fsrc = shader + ".fs";

	vertex = Shader(vsrc, GL_VERTEX_SHADER);
    fragment = Shader(fsrc, GL_FRAGMENT_SHADER);

    link();
}

ShaderProgram::~ShaderProgram()
{
	
}

void ShaderProgram::setUniformMat4(const std::string &name, const Matrix4f &mat)
{
    GLuint toSetLoc;

    toSetLoc = glGetUniformLocation(this->programID, name.c_str());

    glUniformMatrix4fv(toSetLoc, 1, GL_FALSE, mat.m.data());
}

void ShaderProgram::setUniformVec3(const std::string &name, const Vector3f &vec)
{
    GLuint toSetLoc;

    toSetLoc = glGetUniformLocation(this->programID, name.c_str());

    glUniform3fv(toSetLoc, 1, vec.data());
}

void ShaderProgram::setUniformFloat(const std::string &name, const float &f)
{
    GLuint toSetLoc;

    toSetLoc = glGetUniformLocation(this->programID, name.c_str());

    glUniform1f(toSetLoc, f);
}

void ShaderProgram::setUniformInt(const std::string &name, const int &i)
{
    GLuint toSetLoc;

    toSetLoc = glGetUniformLocation(this->programID, name.c_str());

    glUniform1i(toSetLoc, i);
}


void ShaderProgram::use()
{
	glUseProgram(programID);
}

unsigned int ShaderProgram::getID() const
{
	return programID;
}


void ShaderProgram::link(void)
{
	unsigned int vid;
    unsigned int fid;

    vid = vertex.compile();
    fid = fragment.compile();

	programID = glCreateProgram();
	if (!programID)
		return ;

	glAttachShader(programID, vid);
    glAttachShader(programID, fid);

	GLint success;
    GLchar errLog[1204];

    glLinkProgram(programID);
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(programID, 1024, NULL, errLog);
        std::cerr << "Error linking shader program : " << errLog <<  "\n";
        exit(1);
    }

    glValidateProgram(programID);
    glGetProgramiv(programID, GL_VALIDATE_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(programID, 1024, NULL, errLog);
        std::cerr << "Error linking shader program : " << errLog <<  "\n";
        exit(1);
    }

    glDeleteShader(vid);
    glDeleteShader(fid);
}