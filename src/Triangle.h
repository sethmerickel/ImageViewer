#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ShaderProgram.h"

class Triangle
{
public:
   Triangle();
   friend void draw(Triangle& triangle);

private:
  GLuint m_vbo_id;
  GLuint m_vao_id;
  GLuint m_ebo_id;
  ShaderProgram m_sp;
};
