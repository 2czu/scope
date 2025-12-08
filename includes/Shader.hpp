/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 10:37:13 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/08 10:23:44 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../third_party/glad/glad.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
	private:
		std::string path;
		GLenum type;
		unsigned int id;

	public:
		Shader() {};
		Shader(const std::string& shaderPath, GLenum shaderType);
		Shader(const Shader &other);
		Shader &operator=(const Shader &other);
		~Shader();

    unsigned int	compile();
    unsigned int	getID() const;
	GLenum			getType() const;
	std::string		&getPath();
};
