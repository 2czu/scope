/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Material.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:43:52 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/25 14:54:11 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ShaderProgram.hpp"

class Texture
{
	public :
		Texture(const std::string &texturefile);
		~Texture() {};

		unsigned int	textureID;
		unsigned char	*data;
		int				width;
		int				height;
		int				nrChannels;
		
		void	bind();
		void	unbind();
};

class Material
{
	public :
		Material(const std::string &shadertype, const std::string &texturefile) : shader(shadertype), texture(texturefile) {};
		~Material() {};

		ShaderProgram	shader;
		Texture			texture;
};