/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texture.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:43:12 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/02 19:00:22 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Material.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../third_party/stb/stb_image.h"

Texture::Texture(const std::string &texturefile)
{

	stbi_set_flip_vertically_on_load(true);
	data = stbi_load_16(texturefile.c_str(), &width, &height, &nrChannels, 0);
	if (!data) {
   		printf("Failed: %s\n", stbi_failure_reason());
	} else {
		printf("Loaded!\n");
	}

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	GLenum format   = (nrChannels == 1 ? GL_RED  :
                    nrChannels == 3 ? GL_RGB  :
                                      GL_RGBA);

	GLenum internal = (nrChannels == 1 ? GL_R16  :
						nrChannels == 3 ? GL_RGB16 :
										GL_RGBA16);

	std::cout << format << std::endl;

	glTexImage2D(GL_TEXTURE_2D, 0, internal, width, height, 0, format, GL_UNSIGNED_SHORT, data);
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