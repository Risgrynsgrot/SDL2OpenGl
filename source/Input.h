#pragma once
#include "SDL2/SDL.h"
#include <unordered_map>
#include "glm/glm.hpp"

#define INPUT Input::GetInstance()
enum KeyStatus
{
    Up,
    Pressed,
    Down,
    Released
};

class Input
{
friend class Game;
public:
    static Input* GetInstance();
    bool GetKeyPressed(SDL_Scancode aKeyCode);
    bool GetKeyDown(SDL_Scancode aKeyCode);
    bool GetKeyReleased(SDL_Scancode aKeyCode);
    bool GetKeyUp(SDL_Scancode aKeyCode);
    glm::vec2 GetMouseMovement();
    void Update();


    Input(Input &other) = delete;
    void operator=(const Input&) = delete;
    ~Input();

private:
    Input();
    const Uint8* myCurrentFrameKeyState;
    Uint8* myLastFrameKeyState;
    int myKeyCount;
    glm::vec2 myMouseMovement;
    static Input* myInstance;
};