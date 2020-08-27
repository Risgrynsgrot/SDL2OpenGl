#include "Game.h"
#include <cmath>
#include "ShaderUtility.h"
#include "stb_image.h"
#include "Math.h"

Game::Game()
{

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

    //configure global opengl state
    glEnable(GL_DEPTH_TEST);

    myShader = Shader("res/shaders/Basic.glsl");

    //    float vertices[] =
    //    {
    //         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
    //         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
    //        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
    //        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
    //
    //    };
    float vertices[] = 
    {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
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

    //Setup EBO
    glGenBuffers(1, &myEBO);

    //Setup Vertex array object
    glGenVertexArrays(1, &myVAO);

    //Bind vertex array object
    glBindVertexArray(myVAO);

    //Copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, myVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //TEMPORARILY COMMENTED OUT
    //copy our index array in a element buffer for OpenGL to use
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myEBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //then set our vertex attributes pointers
    //Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    //Color
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);
    //Texture coords
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Load a texture
    glGenTextures(1, &myTexture);
    glBindTexture(GL_TEXTURE_2D, myTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    unsigned char *imgData = stbi_load("res/sprites/circle.png", &width, &height, &nrChannels, STBI_rgb_alpha);

    if (imgData != nullptr)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load Texture" << std::endl;
    }
    stbi_image_free(imgData);

    myShader.Use();

    myShader.SetInt("texture1", 0);

    //perspective projection, set here because it doesn't change
    myProjection = glm::perspective(glm::radians(90.f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.f);
    myShader.SetMat4("projection", myProjection);

    GameInit();

    return true;
}

void Game::GameInit()
{
    myCamera.Init();
}


bool Game::Update(float aDeltaTime)
{
    //Polling events and updating input stuff
    while (SDL_PollEvent(&myWindowEvent))
    {
        switch (myWindowEvent.type)
        {
        case SDL_MOUSEMOTION:
            INPUT->myMouseMovement = glm::vec2(myWindowEvent.motion.xrel, myWindowEvent.motion.yrel);
            break;
        case SDL_QUIT:
            return true;
        }
    }
    myCamera.Update(aDeltaTime);

    //Update gamelogic

    //Update keystates last, maybe do a beginning of frame and end of frame, because I think this makes the input have 1 frame of lag
    INPUT->Update();

    //Draw opengl stuff
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, myTexture);

    myShader.Use();

    auto timeValue = SDL_GetTicks();
    float fTime = timeValue / 1000.f;

    //Transforms for the model
    myModel = glm::mat4(1.0f);
    myModel = glm::rotate(myModel, fTime * glm::radians(50.f), glm::vec3(0.5f, 1.0f, 0.0f));

    myShader.SetMat4("model", myModel);
    myShader.SetMat4("view", myCamera.GetViewMatrix());

    glBindVertexArray(myVAO);
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    SDL_GL_SwapWindow(myGWindow);

    return false;
}

void Game::Start()
{
    myFinished = false;
    auto lastFrameTime = SDL_GetTicks();
    auto currentFrameTime = SDL_GetTicks();
    float deltaTime = 0.f;
    while (!myFinished)
    {
        currentFrameTime = SDL_GetTicks();
        deltaTime = (currentFrameTime - lastFrameTime);
        deltaTime *= 0.01;
        lastFrameTime = currentFrameTime;
        //printf("current: %d, last: %d, delta: %f\n", currentFrameTime, lastFrameTime, deltaTime);
        myFinished = Update(deltaTime);
    }

    glDeleteVertexArrays(1, &myVAO);
    glDeleteBuffers(1, &myVBO);
    glDeleteBuffers(1, &myEBO);

    SDL_DestroyWindow(myGWindow);
    SDL_Quit();
}
