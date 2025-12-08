/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:20:44 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/08 15:58:40 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Application.hpp"

// GLuint VBO;
// GLuint VAO;
// GLuint EBO;
// unsigned int texture;
// unsigned int viewLoc = 0;
// unsigned int modelLoc = 0;
// unsigned int projectionLoc = 0;

// int windowWidth = 1920;
// int windowHeight = 1080;
// // GLint redColorLocation = 0;


// struct Image {
//     int width;
//     int height;
//     std::vector<unsigned char> pixels;
// };


// static void skipComments(std::ifstream& f) {
//     while (f.peek() == '#') {
//         std::string line;
//         std::getline(f, line);
//     }
// }

// Image loadPPM(const std::string& path) {
//     std::ifstream f(path, std::ios::binary);
//     if (!f) throw std::runtime_error("Cannot open PPM");

//     std::string magic;
//     f >> magic;
//     if (magic != "P6") throw std::runtime_error("Not a P6 PPM");

//     skipComments(f);
//     int w, h;
//     f >> w >> h;

//     skipComments(f);
//     int maxv;
//     f >> maxv;
//     if (maxv != 255) throw std::runtime_error("Unsupported max value");

//     f.get();

//     Image img;
//     img.width = w;
//     img.height = h;
//     img.pixels.resize(w * h * 3);

//     f.read(reinterpret_cast<char*>(img.pixels.data()), img.pixels.size());
//     if (!f) throw std::runtime_error("Error reading pixel data");

//     return img;
// }

//     glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &VBO);
//     glGenBuffers(1, &EBO);

//     glBindVertexArray(VAO);
//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);
//     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
//     glEnableVertexAttribArray(1);
//     glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//     glEnableVertexAttribArray(2);

//     glGenTextures(1, &texture);
//     glBindTexture(GL_TEXTURE_2D, texture);

//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//     Image textoure = loadPPM("./textures/kirby.ppm");
//     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textoure.width, textoure.height, 0, GL_RGB, GL_UNSIGNED_BYTE, textoure.pixels.data());
//     glGenerateMipmap(GL_TEXTURE_2D);
// }

int main(void)
{
    Application app;
    app.run();
}