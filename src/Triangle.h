#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Texture.h"

class ShaderProgram;

class Triangle
{
public:
   Triangle(const ShaderProgram& sp);
   Triangle(Triangle&& tri);
   Triangle& operator=(Triangle&& rhs);

   friend void draw(Triangle& triangle, ShaderProgram& sp);
   friend void update(Triangle& triangle);

private:
  GLuint m_vbo_id;
  GLuint m_vao_id;
  GLuint m_ebo_id;
  Texture m_texture;
};
