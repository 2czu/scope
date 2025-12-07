/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Material.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:43:52 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/06 15:10:35 by pacda-si         ###   ########.fr       */
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
		uint16_t		*data;
		int				width;
		int				height;
		int				nrChannels;
		
		void	bind();
		void	unbind();
};

class Material
{
	public :
		Material() : texture(NULL) {};
		~Material() {};

		void print() const;
		void bind(ShaderProgram *shader);

		float			ns;
		Vector3f		ka;
		Vector3f		kd;
		Vector3f		ks;
		float			d;
		float			illum;
		std::string		name;

		Texture			*texture;
};