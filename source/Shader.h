#pragma once
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <string>
#include <glm/glm.hpp>

class Shader
{
    public:

        Shader();
        Shader(const char* aFilePath);

        void Use();
        void SetBool(const std::string& aName, bool aValue);
        void SetInt(const std::string& aName, int aValue);
        void SetFloat(const std::string& aName, float aValue);
        void SetMat4(const std::string& aName, const glm::mat4& aValue);
        unsigned int GetId();
    private:
        unsigned int myId;
        void CheckCompileErrors(unsigned int aShader, std::string aType);

};