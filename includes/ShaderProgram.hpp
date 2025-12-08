/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShaderProgram.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 11:40:17 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/08 13:50:36 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Shader.hpp"
#include "Math.hpp"
#include <vector>
#include <cstring>
#include <memory>

class ShaderProgram
{
	private:
		unsigned int		programID;
		Shader				vertex;
		Shader				fragment;

	public:
		ShaderProgram(const std::string &shader);
		ShaderProgram(const ShaderProgram &other);
		ShaderProgram &operator=(const ShaderProgram &other);
		~ShaderProgram();

		void				setUniformMat4(const std::string &name, const Matrix4f &mat);
		void 				setUniformVec3(const std::string &name, const Vector3f &vec);
		void 				setUniformFloat(const std::string &name, const float &f);
		void				setUniformInt(const std::string &name, const int &i);

		void				link(void);
		void				use();
		unsigned int		getID() const;
};