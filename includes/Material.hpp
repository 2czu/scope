/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Material.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:43:52 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/12 17:09:49 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ShaderProgram.hpp"

struct Image {
    unsigned int width;
    unsigned int height;
    std::vector<unsigned char> pixels;
};

struct Texture
{
	unsigned int	textureID; 
	Image			image;

	Texture(const std::string &texturefile);
	~Texture() {};

	void	bind();
	void	unbind();
};

struct Material
{
	float			ns;
	Vector3f		ka;
	Vector3f		kd;
	Vector3f		ks;
	float			d;
	float			illum;
	std::string		name;

	Material();
	Material(const Material &other);
	~Material() {};

	void		print() const;
	void		bind(ShaderProgram *shader);
	Material	*clone(void);
};