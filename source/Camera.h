#pragma once

#include "SDL2/SDL.h"
#include "glm/glm.hpp"

class Camera
{
public:
    void Init();
    void Update(float aDeltaTime);
    const glm::mat4& GetViewMatrix();

private:
    void HandleInput();
    SDL_bool myLockCursor = SDL_FALSE;
    bool firstMouse;

    const float myCameraSpeed = 1.f;
    glm::vec3 myCameraPosition;
    float pitch;
    float yaw;
    glm::vec3 myUp;
    glm::vec3 myCameraUp;
    glm::vec3 myCameraFront;
    glm::vec3 myCameraTarget;
    glm::vec3 myCameraDirection;
    glm::mat4 myView;
    glm::vec3 myCameraMoveVector;
};