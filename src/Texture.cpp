#include "Texture.h"

#include <array>
#include <iostream>
#include <stdexcept>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "stb/stb_image.h"

//-----------------------------------------------------------------------------

Texture::Texture(const std::string& fname)
  :m_width(-1),
   m_height(-1),
   m_channels(0)
{
   // Read texture from disk
   auto data = stbi_load(fname.c_str(), &m_width, &m_height, &m_channels, 0);

   //GLubyte data[] = { 0xff, 0x09, 0x00, 0xff,
   //                   0xff, 0xff, 0x00, 0xff,
   //                   0x00, 0xff, 0x00, 0xff, 
   //                   0xff, 0x00, 0xff, 0xff };
       
   //m_width = 2;
   //m_height = 2;
   //m_channels = 4;
   std::cout << "Width: " << m_width << std::endl;
   std::cout << "Height: " << m_height << std::endl;
   std::cout << "Channels: " << m_channels << std::endl;

   if (data == nullptr)
   {
      std::stringstream msg;
      msg << "Failed to read texture: ";
      msg << fname;
      throw std::runtime_error(msg.str());
   }

   // Load texture to graphics card
   glGenTextures(1, &m_id);
   bind();
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
   glTexImage2D(
         GL_TEXTURE_2D,
         0, 
         GL_RGB,
         m_width,
         m_height,
         0,
         GL_RGB,
         GL_UNSIGNED_BYTE,
         data);

   unBind();


   // Free memory
   stbi_image_free(data);
}

//-----------------------------------------------------------------------------

Texture::Texture(Texture&& rhs)
  :m_id(rhs.m_id),
   m_width(rhs.m_width),
   m_height(rhs.m_height),
   m_channels(rhs.m_channels)
{
   m_id = rhs.m_id;
   rhs.m_id = 0;
}

//-----------------------------------------------------------------------------

Texture& Texture::operator=(Texture&& rhs)
{
   m_width = rhs.m_width;
   m_height = rhs.m_height;
   m_channels = rhs.m_channels;
   m_id = rhs.m_id;
   rhs.m_id = 0;
}

//-----------------------------------------------------------------------------

Texture::~Texture()
{
   glDeleteTextures(1, &m_id);
}
   
//-----------------------------------------------------------------------------

GLuint Texture::getId() const 
{
   return m_id;
}

//-----------------------------------------------------------------------------

void
Texture::bind()
{
   glBindTexture(GL_TEXTURE_2D, m_id);
}

//-----------------------------------------------------------------------------

void
Texture::unBind()
{
   glBindTexture(GL_TEXTURE_2D, 0);
}

//-----------------------------------------------------------------------------
