#pragma once
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

class Game
{
    public:
        bool Init();
        void Start();
        bool InitGL();
        void HandleKeys(unsigned char aKey, int aX, int aY);
        bool Update();
        void Render();
        void Close();
    private:
        SDL_Window* myGWindow = NULL;
        SDL_GLContext myGContext;
        bool myGRenderQuad = true;
        const GLint SCREEN_WIDTH = 1280;
        const GLint SCREEN_HEIGHT = 720;
        SDL_Event myWindowEvent;
        bool myFinished;
        unsigned int myVBO;
        unsigned int myVAO;
        unsigned int myEBO;
        unsigned int myShaderProgram;

};
