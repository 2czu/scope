/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texture.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:43:12 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/25 14:53:38 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Material.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../third_party/stb/stb_image.h"

Texture::Texture(const std::string &texturefile)
{

	stbi_set_flip_vertically_on_load(true);
	data = stbi_load(texturefile.c_str(), &width, &height, &nrChannels, 0);
	if (!data)
	{
		std::cout << "tex failed to load at path: " << texturefile << std::endl;
		return;
	}

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	GLenum format = GL_RGB;
	if (nrChannels == 1)
		format = GL_RED;
	else if (nrChannels == 3)
		format = GL_RGB;
	else if (nrChannels == 4)
		format = GL_RGBA;

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	unbind();
}

void	Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void	Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}