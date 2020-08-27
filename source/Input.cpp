#include "Input.h"

    Input* Input::myInstance;

    Input::Input()
    {
        myKeyCount = 0;
        myCurrentFrameKeyState = SDL_GetKeyboardState(&myKeyCount);
        myLastFrameKeyState = new Uint8[myKeyCount];
    }
    Input::~Input()
    {
        delete myLastFrameKeyState;
    }

    bool Input::GetKeyPressed(SDL_Scancode aKeyCode)
    {
        //printf("%s has state %d this frame and %d last frame\n", SDL_GetScancodeName(aKeyCode), myCurrentFrameKeyState[aKeyCode], myLastFrameKeyState[aKeyCode]);
        return myCurrentFrameKeyState[aKeyCode] && !myLastFrameKeyState[aKeyCode];
    }
    bool Input::GetKeyDown(SDL_Scancode aKeyCode)
    {
        //printf("%s has state %d\n", SDL_GetScancodeName(aKeyCode), myCurrentFrameKeyState[aKeyCode]);
        return myCurrentFrameKeyState[aKeyCode];
    }
    bool Input::GetKeyReleased(SDL_Scancode aKeyCode)
    {
        return !myCurrentFrameKeyState[aKeyCode] && myLastFrameKeyState[aKeyCode];
    }
    bool Input::GetKeyUp(SDL_Scancode aKeyCode)
    {
        return !myCurrentFrameKeyState[aKeyCode];
    }
    void Input::Update()
    {
        myMouseMovement = glm::vec2(0.f, 0.f);
        memcpy(myLastFrameKeyState, myCurrentFrameKeyState, myKeyCount * sizeof(*myLastFrameKeyState));
        myCurrentFrameKeyState = SDL_GetKeyboardState(&myKeyCount);
    }
    glm::vec2 Input::GetMouseMovement()
    {
        return myMouseMovement;
    }
    Input* Input::GetInstance()
    {
        if(myInstance == nullptr)
        {
            myInstance = new Input();
        }
        return myInstance;
    }