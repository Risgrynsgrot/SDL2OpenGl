#include "Shader.h"
#include "ShaderUtility.h"

Shader::Shader()
{

}

Shader::Shader(const char* aFilePath)
{
    ShaderProgramSource shaderSource = ParseShader(aFilePath);

    unsigned int vertex;
    unsigned int fragment;

    //vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexCString = shaderSource.VertexSource.c_str();
    glShaderSource(vertex, 1, &vertexCString, NULL);
    glCompileShader(vertex);
    CheckCompileErrors(vertex, "VERTEX");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentCString = shaderSource.FragmentSource.c_str();
    glShaderSource(fragment, 1, &fragmentCString, NULL);
    glCompileShader(fragment);
    CheckCompileErrors(fragment, "FRAGMENT");

    myId = glCreateProgram();
    glAttachShader(myId, vertex);
    glAttachShader(myId, fragment);
    glLinkProgram(myId);
    CheckCompileErrors(myId, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}
void Shader::CheckCompileErrors(unsigned int aShader, std::string aType)
{
    int success;
    char infoLog[1024];
    if(aType == "PROGRAM")
    {
        glGetProgramiv(aShader, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(aShader, 512, NULL, infoLog);
            std::cout << "ERROR: ShaderProgram of type " << aType << " Failed to Link\n" << infoLog;
        }
    }
    else
    {
        glGetShaderiv(aShader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(aShader, 512, NULL, infoLog);
            std::cout << "ERROR: Shader of type " << aType << " Failed to compile\n" << infoLog;
        }
    }
}

void Shader::Use()
{
    glUseProgram(myId);
}

void Shader::SetBool(const std::string& aName, bool aValue)
{
    glUniform1i(glGetUniformLocation(myId, aName.c_str()), (int)aValue);
}
void Shader::SetInt(const std::string& aName, int aValue)
{
    glUniform1i(glGetUniformLocation(myId, aName.c_str()), aValue);
}
void Shader::SetFloat(const std::string& aName, float aValue)
{
    glUniform1f(glGetUniformLocation(myId, aName.c_str()), aValue);
}
