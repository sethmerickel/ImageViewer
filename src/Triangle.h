#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Triangle
{
public:
   Triangle();
   friend void draw(Triangle& triangle);
   friend void update(Triangle& triangle);

private:
  GLuint m_vbo_id;
  GLuint m_vao_id;
  GLuint m_ebo_id;
};
