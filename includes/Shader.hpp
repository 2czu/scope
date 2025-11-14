/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 10:37:13 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/14 12:30:41 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "glad/glad.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#pragma once
#include "glad/glad.h"
#include <string>
#include <iostream>

class Shader
{
	private:
		std::string path;
		GLenum type;
		unsigned int id;

	public:
		Shader(const std::string& shaderPath, GLenum shaderType);
		~Shader();

    unsigned int	compile();
    unsigned int	getID() const;
	GLenum			getType() const;
	std::string		&getPath();
};
