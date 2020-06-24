#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/GLU.h>
#include <stdio.h>
#include <string>
#include "Game.h"

bool Game::Init()
{
    bool success = true;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //OpenGl 2.1
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

        myGWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if(myGWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            myGContext = SDL_GL_CreateContext(myGWindow);
            if(myGContext == NULL)
            {
                printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                if(!InitGL())
                {
                    printf("Failed to initialize OpenGL!\n");
                    success = false;
                }
            }
        }
    }
    return success;
}

bool Game::InitGL()
{
    bool success = true;
    GLenum error = GL_NO_ERROR;

    //Init projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    error = glGetError();
    if(error != GL_NO_ERROR)
    {
        printf("Error initizalizing OpenGL! %s\n", gluErrorString(error));
        success = false;
    }

    //Initialize ModelView Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    error = glGetError();
    if(error != GL_NO_ERROR)
    {
        printf("Error initializing OpenGL! %s\n", gluErrorString(error));
        success = false;
    }

    //Initialize clear color
    glClearColor(0.f, 0.f, 0.f, 1.f);

    error = glGetError();
    if(error != GL_NO_ERROR)
    {
        printf("Error initializing OpenGL! %s\n", gluErrorString(error));
        success = false;
    }


    return success;
}

void Game::HandleKeys(unsigned char aKey, int aX, int aY)
{
    if(aKey == 'q')
    {
        myGRenderQuad = !myGRenderQuad;
    }
}

void Game::Update()
{
}

void Game::Render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if(myGRenderQuad)
    {
        glBegin(GL_QUADS);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.5f, -0.5f);
        glVertex2f(0.5f, 0.5f);
        glVertex2f(-0.5f, 0.5f);
        glEnd();
    }
}

void Game::Start()
{
    bool quit = false;
    SDL_Event e;
    //Enable text input
    SDL_StartTextInput();

    //While application is running
    while( !quit )
    {
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            //Handle keypress with current mouse position
            else if( e.type == SDL_TEXTINPUT )
            {
                int x = 0, y = 0;
                SDL_GetMouseState( &x, &y );
                HandleKeys( e.text.text[ 0 ], x, y );
            }
        }

        //Render quad
        Render();

        //Update screen
        SDL_GL_SwapWindow( myGWindow );
    }

    //Disable text input
    SDL_StopTextInput();
}
