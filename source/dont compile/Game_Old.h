#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

class Game
{
    public:
        bool Init();
        void Start();
        bool InitGL();
        void HandleKeys(unsigned char aKey, int aX, int aY);
        void Update();
        void Render();
        void Close();
    private:
        SDL_Window* myGWindow = NULL;
        SDL_GLContext myGContext;
        bool myGRenderQuad = true;
        const int SCREEN_WIDTH = 1280;
        const int SCREEN_HEIGHT = 720;
};
