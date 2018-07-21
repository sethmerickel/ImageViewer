#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Texture
{
public:
   Texture(const std::string& fname);
   void bind();
   void unBind();
private:
   GLuint m_id;
   int m_width;
   int m_height;
   int m_channels;
};
