/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:20:44 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/17 17:50:55 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../includes/scop.hpp"
#include <SDL2/SDL.h>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

GLuint VBO;
GLuint VAO;
GLuint EBO;
unsigned int texture;
// GLint redColorLocation = 0;

#include <fstream>
#include <vector>
#include <stdexcept>
#include <string>

struct Image {
    int width;
    int height;
    std::vector<unsigned char> pixels;
};


static void skipComments(std::ifstream& f) {
    while (f.peek() == '#') {
        std::string line;
        std::getline(f, line);
    }
}

Image loadPPM(const std::string& path) {
    std::ifstream f(path, std::ios::binary);
    if (!f) throw std::runtime_error("Cannot open PPM");

    std::string magic;
    f >> magic;
    if (magic != "P6") throw std::runtime_error("Not a P6 PPM");

    skipComments(f);
    int w, h;
    f >> w >> h;

    skipComments(f);
    int maxv;
    f >> maxv;
    if (maxv != 255) throw std::runtime_error("Unsupported max value");

    f.get();

    Image img;
    img.width = w;
    img.height = h;
    img.pixels.resize(w * h * 3);

    f.read(reinterpret_cast<char*>(img.pixels.data()), img.pixels.size());
    if (!f) throw std::runtime_error("Error reading pixel data");

    return img;
}


static void createVertexBuffer()
{
    // glEnable(GL_CULL_FACE);
    // glFrontFace(GL_CW);

    float vertices[] = {
    // positions         // colors
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,   // top left
    0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,// bottom right
    0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,   // top right
    };
    // float texCoords[] = {
    //     0.0f, 0.0f,  // lower-left corner  
    //     1.0f, 0.0f,  // lower-right corner
    //     0.5f, 1.0f   // top-center corner
    // };
    unsigned int indices[] =
    {
        0, 1, 2,
        1, 3, 2
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    Image textoure = loadPPM("./textures/kirby.ppm");

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textoure.width, textoure.height, 0, GL_RGB, GL_UNSIGNED_BYTE, textoure.pixels.data());
    glGenerateMipmap(GL_TEXTURE_2D);
}

static void compileShaders(void)
{
    Shader vertex = Shader("./shaders/shader.vs", GL_VERTEX_SHADER);
    Shader fragment = Shader("./shaders/shader.fs", GL_FRAGMENT_SHADER);

    ShaderProgram shaderProgram;

    shaderProgram.attachShader(vertex);
    shaderProgram.attachShader(fragment);
    shaderProgram.link();
    shaderProgram.use();
}

static void render()
{
    static GLclampf red = 0.0f;

    red += 1.0f/256.0f;


    // glUniform1f(redColorLocation, sin(red));
    
    glClear(GL_COLOR_BUFFER_BIT);

    // glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}


int main(int argc, char** argv)
{

    (void)argc;
    (void)argv;

    
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    int windowWidth = 1920;
    int windowHeight = 1080;

    SDL_Window* window = SDL_CreateWindow(
        "Salut", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        windowWidth, windowHeight, 
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        std::cerr << "SDL_GL_CreateContext Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    if (!gladLoadGL()) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // vec3 test

    // Vector3f vertices[1];
    // vertices[0] = Vector3f();
    // vertices[0].print();

    try{
        createVertexBuffer();
        
        compileShaders();        
    }
    catch(std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    bool running = true;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;
        }

        render();

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
