#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Texture
{
public:
   Texture(const std::string& fname);
   ~Texture();

   // Movable
   Texture(Texture&& rhs);
   Texture& operator=(Texture&& rhs);

   // Not copyable
   Texture(const Texture&) = delete;
   Texture& operator=(const Texture&) = delete;

   GLuint getId() const;
   void bind();
   void unBind();

private:
   GLuint m_id;
   int m_width;
   int m_height;
   int m_channels;
};
