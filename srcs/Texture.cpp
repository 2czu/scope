/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texture.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:43:12 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/08 15:16:46 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Material.hpp"

Image loadBMP(const std::string& path) {
    std::ifstream f(path, std::ios::binary);
    if (!f) throw std::runtime_error("Cannot open BMP file");

    unsigned char header[54];
    f.read(reinterpret_cast<char*>(header), 54);
    if (!f) throw std::runtime_error("Cannot read BMP header");

    if (header[0] != 'B' || header[1] != 'M')
        throw std::runtime_error("Not a BMP file");

    int dataOffset = *reinterpret_cast<int*>(&header[0x0A]);
    int width  = *reinterpret_cast<int*>(&header[0x12]);
    int height = *reinterpret_cast<int*>(&header[0x16]);
    unsigned short bitsPerPixel = *reinterpret_cast<unsigned short*>(&header[0x1C]);

    if (bitsPerPixel != 24)
        throw std::runtime_error("Only 24-bit BMP supported");

    size_t row_padded = (width * 3 + 3) & (~3);
    std::vector<unsigned char> buffer(row_padded * height);

    f.seekg(dataOffset, std::ios::beg);
    f.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
    if (!f) throw std::runtime_error("Error reading BMP pixel data");

    Image img;
    img.width = width;
    img.height = height;
    img.pixels.resize(width * height * 3);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            size_t bufIndex = y * row_padded + x * 3;
            size_t imgIndex = (y * width + x) * 3;
            img.pixels[imgIndex + 0] = buffer[bufIndex + 2];
            img.pixels[imgIndex + 1] = buffer[bufIndex + 1];
            img.pixels[imgIndex + 2] = buffer[bufIndex + 0];
        }
    }

    return img;
}


Texture::Texture(const std::string &texturefile)
{

	

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	image = loadBMP(texturefile.c_str());
	
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width, image.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image.pixels.data());
    glGenerateMipmap(GL_TEXTURE_2D);

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