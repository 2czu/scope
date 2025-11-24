/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShaderProgram.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 11:40:17 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/24 13:20:36 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Shader.hpp"
#include "Math.hpp"
#include <vector>

class ShaderProgram
{
	private:
		unsigned int		programID;
		Shader				vertex;
		Shader				fragment;

	public:
		ShaderProgram(const std::string &shader);
		~ShaderProgram();

		void				setUniformMat4(const std::string &name, const Matrix4f &mat);

		void				link(void);
		void				use();
		unsigned int		getID() const;
};