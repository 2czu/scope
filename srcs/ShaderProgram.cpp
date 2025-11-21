/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShaderProgram.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 11:43:46 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/21 16:09:11 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ShaderProgram.hpp"

ShaderProgram::ShaderProgram() : programID(0)
{
	
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

void ShaderProgram::attachShader(const Shader& shader)
{
	shaders.push_back(shader);
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
	std::vector<unsigned int> shaderIDs;

	for (Shader& s : shaders)
	{
		shaderIDs.push_back(s.compile());
	}

	programID = glCreateProgram();
	if (!programID)
		return ;

	for (unsigned int id : shaderIDs)
		glAttachShader(programID, id);

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

	for (unsigned int id : shaderIDs)
		glDeleteShader(id);
}