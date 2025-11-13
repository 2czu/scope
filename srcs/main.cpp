/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:20:44 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/13 12:00:33 by pacda-si         ###   ########.fr       */
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
GLuint VBO2;
GLuint VAO;
GLuint VAO2;
GLint gScaleLocation = 0;

const char *pVSFileName = "./shaders/shader.vs";
const char *pFSFileName = "./shaders/shader.fs";

static void createVertexBuffer()
{
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);

    Vector3f triangle1[3];
    triangle1[0] = Vector3f(-0.5f, -0.5f, 0.0f);
    triangle1[1] = Vector3f(-0.5f, 0.5f, 0.0f);
    triangle1[2] = Vector3f(0.5f, -0.5f, 0.0f);
    
    Vector3f triangle2[3];
    triangle2[0] = Vector3f(-0.45f, 0.55f, 0.0f);
    triangle2[1] = Vector3f(0.55f, 0.55f, 0.0f);
    triangle2[2] = Vector3f(0.55f, -0.45f, 0.0f);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);

    glGenBuffers(1, &VBO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);
}

static bool readFile(const char* pFileName, std::string &outfile)
{
    std::ifstream f(pFileName);
    bool ret = false;

    if (f.is_open())
    {
        std::string line;
        while(getline(f, line))
        {
            outfile.append(line);
            outfile.append("\n");
        }

        f.close();
        ret = true;
    }
    else
    {
        std::string fileName(pFileName);
        std::cerr << "Couldn't open " << fileName << ".\n";
    }
    return (ret);
    
}

static void addShader(GLuint shaderProgram, const char *shaderText, GLenum shaderType)
{
    GLuint shaderObject = glCreateShader(shaderType);
    
    if (!shaderObject)
    {
        std::cerr << "Error creating shader type : " << shaderType << "\n";
        exit(1);
    }

    const GLchar *p[1];
    p[0] = shaderText;
    
    GLint lengths[1];
    lengths[0] = strlen(shaderText);

    glShaderSource(shaderObject, 1, p, lengths);

    glCompileShader(shaderObject);

    GLint success;
    glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        GLchar infoLog[1024];
        glGetShaderInfoLog(shaderObject, 1024, NULL, infoLog);
        std::cerr << "Error compiling shader type : " << shaderType << ", " << infoLog <<  "\n";
        exit(1);
    }

    glAttachShader(shaderProgram, shaderObject);

}

static void compileShaders(void)
{
    GLuint shaderProgram = glCreateProgram();
    
    if (!shaderProgram)
    {
        std::cerr << "Error creating shader program\n";
        exit(1);
    }

    std::string vs, fs; // vertex, fragment shader

    if (!readFile(pVSFileName, vs) || !readFile(pFSFileName, fs))
        exit(1);
    
    addShader(shaderProgram, vs.c_str(), GL_VERTEX_SHADER);
    addShader(shaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

    GLint success;
    GLchar errLog[1204];

    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shaderProgram, 1024, NULL, errLog);
        std::cerr << "Error linking shader program : " << errLog <<  "\n";
        exit(1);
    }

    gScaleLocation = glGetUniformLocation(shaderProgram, "gScale");
    if (gScaleLocation == -1)
    {
        std::cerr << "Error getting uniform location of gScale : "<<  "\n";
        exit(1);
    }

    glValidateProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shaderProgram, 1024, NULL, errLog);
        std::cerr << "Error linking shader program : " << errLog <<  "\n";
        exit(1);
    }

    glUseProgram(shaderProgram);

}

static void render()
{
    // static GLclampf red = 0.0f;

    // red += 1.0f/256.0f;
    // if (red >= 1.0f)
    //     red = 0.0f;

    // glClearColor(red, 0.0f, 0.0f, 1.0f);

    static float Scale = 0.0f;
    Scale += 0.05f;
    glUniform1f(gScaleLocation, sinf(Scale));
    
    glClear(GL_COLOR_BUFFER_BIT);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
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

    compileShaders();

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
