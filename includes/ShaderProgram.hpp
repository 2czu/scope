/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShaderProgram.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 11:40:17 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/14 12:26:27 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Shader.hpp"
#include <vector>

class ShaderProgram
{
	private:
		unsigned int programID;
		std::vector<Shader> shaders;

	public:
		ShaderProgram();
		~ShaderProgram();

		void attachShader(const Shader& shader);

		void			link(void);
		void			use();
		unsigned int	getID() const;
};