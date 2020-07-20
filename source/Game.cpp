#include "Game.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <cmath>

ShaderProgramSource Game::ParseShader(const std::string& aFilePath)
{
    enum class ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };
    ShaderType type = ShaderType::NONE;
    std::ifstream stream(aFilePath);

    std::string line;
    std::stringstream ss[2];
    while(getline(stream, line))
    {
        if(line.find("#shader") != std::string::npos)
        {
            if(line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if(line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }

    return {ss[0].str(), ss[1].str()};
}

bool Game::Init()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    myGWindow = SDL_CreateWindow("OpenGl tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

    myGContext = SDL_GL_CreateContext(myGWindow);

    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return false;
    }

    float vertices[] =
    {
         0.5f,  0.5f, 0.0f, //Top right
         0.5f, -0.5f, 0.0f, //Bottom right
        -0.5f, -0.5f, 0.0f, //Bottom left
        -0.5f,  0.5f, 0.0f  //Top left

    };

    unsigned int indices[] =
    {
        0, 1, 3, //first triangle
        1, 2, 3  //second triangle
    };
    //Setup vertex buffer
    glGenBuffers(1, &myVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Get shader from file
    ShaderProgramSource source = ParseShader("res/shaders/Basic.glsl");

    //Create vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexSource = source.VertexSource.c_str();
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    //Check for errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }

    //Create fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentSource = source.FragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    //Check for errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }

    //Create and link the shaderProgram
    myShaderProgram = glCreateProgram();
    glAttachShader(myShaderProgram, vertexShader);
    glAttachShader(myShaderProgram, fragmentShader);
    glLinkProgram(myShaderProgram);

    //Check for errors
    glGetProgramiv(myShaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(myShaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }


    //Delete shaders, they are already inside the shader program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //Setup EBO
    glGenBuffers(1, &myEBO);

    //Setup Vertex array object
    glGenVertexArrays(1, &myVAO);

    //Bind vertex array object
    glBindVertexArray(myVAO);

    //Copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, myVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //copy our index array in a element buffer for OpenGL to use
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //then set our vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    return true;
}

bool Game::Update()
{
    if(SDL_PollEvent(&myWindowEvent))
    {
        if(myWindowEvent.type == SDL_QUIT)
        {
            return true;
        }
    }

    //Update gamelogic

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    //Draw opengl stuff

    glUseProgram(myShaderProgram);

    auto timeValue = SDL_GetTicks();
    float fTime = timeValue / 1000.f;
    float greenValue = sin(fTime) / 2.0f + 0.5f;
    int vertexColorLocation = glGetUniformLocation(myShaderProgram, "ourColor");
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

    glBindVertexArray(myVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    SDL_GL_SwapWindow(myGWindow);

    return false;
}

void Game::Start()
{
    myFinished = false;
    while(!myFinished)
    {
        myFinished = Update();
    }
    SDL_DestroyWindow(myGWindow);
    SDL_Quit();
}
