#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class ShaderProgram
{
public:
   ShaderProgram();
   
   ~ShaderProgram();

   // Non copyable
   ShaderProgram(const ShaderProgram&) = delete;

   // Non copyable
   ShaderProgram& operator=(const ShaderProgram&) = delete;

   ShaderProgram(ShaderProgram&& shader_program);

   void attachShader(GLuint shader_id);

   //void detachShader(ShaderType type);

   void link();

   void use();

   void disable();

private:
   GLuint m_id;
};
