#pragma once
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "Shader.h"
#include <string>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Input.h"
#include "Camera.h"
#include "Constants.h"


class Game
{
    public:
        Game();
        bool Init();
        void GameInit();
        void Start();
        bool Update(float aDeltaTime);
        void Render();
        void Close();
    private:
        void HandleInput();
        SDL_Window* myGWindow = NULL;
        SDL_GLContext myGContext;
        bool myGRenderQuad = true;
        SDL_Event myWindowEvent;
        bool myFinished;
        unsigned int myVBO;
        unsigned int myVAO;
        unsigned int myEBO;
        unsigned int myShaderProgram;
        unsigned int myTexture;
        Shader myShader;
        glm::mat4 myProjection;
        glm::mat4 myModel;
        Camera myCamera;

};
