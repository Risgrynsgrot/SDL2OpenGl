#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Constants.h"
#include "Input.h"

void Camera::HandleInput()
{
    if(INPUT->GetKeyPressed(SDL_SCANCODE_F1))
    {
        printf("toggling lockcursor thing\n");
        myLockCursor = myLockCursor == SDL_FALSE ? SDL_TRUE : SDL_FALSE;
        SDL_WarpMouseInWindow(NULL, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
        if(SDL_SetRelativeMouseMode(myLockCursor) == 0)
        {
            printf("succeeded in toggle\n");
        }
    }
    myCameraMoveVector = glm::vec3(0.f, 0.f, 0.f);
    myCameraMoveVector.x = (float)INPUT->GetKeyDown(SDL_SCANCODE_D) - (float)INPUT->GetKeyDown(SDL_SCANCODE_A);
    myCameraMoveVector.z = (float)INPUT->GetKeyDown(SDL_SCANCODE_W) - (float)INPUT->GetKeyDown(SDL_SCANCODE_S);
    myCameraMoveVector.y = (float)INPUT->GetKeyDown(SDL_SCANCODE_SPACE) - (float)INPUT->GetKeyDown(SDL_SCANCODE_LCTRL);

    glm::vec2 mouseMovement = INPUT->GetMouseMovement();
    //printf("x: %f y: %f\n", mouseMovement.x, mouseMovement.y);
    mouseMovement *= 0.3f;
    yaw += mouseMovement.x;
    pitch -= mouseMovement.y;

    //pitch = Math::clamp(pitch, -89.f, 89.f);    
    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;
    printf("CameraAngle: pitch: %f yaw: %f\n", pitch, yaw);

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    //printf("Direction: x: %f y: %f z: %f\n", direction.x, direction.y, direction.z);
    if(myLockCursor == SDL_TRUE)
    {
        if(firstMouse)
        {
            firstMouse = false;
            yaw = -90.f;
            pitch = 0.f;
        }
        else
        {
            myCameraFront = glm::normalize(direction);
        }
    }
    else
    {
        firstMouse = true;
    }
    
}
void Camera::Init()
{
    myCameraPosition = glm::vec3(0.f, 0.f, 3.f);

    myUp = glm::vec3(0.f, 1.f, 0.f);

    myCameraUp = glm::vec3(0.f, 1.f, 0.f);
    myCameraFront = glm::vec3(0.f, 0.f, -1.f);
}
void Camera::Update(float aDeltaTime)
{
    HandleInput();
    myCameraPosition += glm::normalize(glm::cross(myCameraFront, myCameraUp)) * myCameraMoveVector.x * myCameraSpeed * aDeltaTime;
    myCameraPosition += myCameraUp * myCameraMoveVector.y * myCameraSpeed * aDeltaTime;
    myCameraPosition += myCameraFront * myCameraMoveVector.z * myCameraSpeed * aDeltaTime;

    myView = glm::lookAt(myCameraPosition, myCameraPosition + myCameraFront, myCameraUp);
}
const glm::mat4& Camera::GetViewMatrix()
{
    return myView;
}