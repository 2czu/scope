/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:20:44 by pacda-si          #+#    #+#             */
/*   Updated: 2025/10/11 11:55:42 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../includes/scop.hpp"
#include <SDL2/SDL.h>
GLuint VBO;

static void createVertexBuffer()
{
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);

    Vector3f vertices[3];
    vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
    vertices[1] = Vector3f(0.0f, 1.0f, 0.0f);
    vertices[2] = Vector3f(1.0f, -1.0f, 0.0f);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

static void render()
{
    // static GLclampf red = 0.0f;

    // red += 1.0f/256.0f;
    // if (red >= 1.0f)
    //     red = 0.0f;

    // glClearColor(red, 0.0f, 0.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glDisableVertexAttribArray(0);
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
    createVertexBuffer();

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
