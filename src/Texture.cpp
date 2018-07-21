#include "Texture.h"

#include <array>
#include <iostream>
#include <stdexcept>
#include <sstream>

#include "stb/stb_image.h"

//-----------------------------------------------------------------------------

Texture::Texture(const std::string& fname)
  :m_width(-1),
   m_height(-1),
   m_channels(0)
{
   // Read texture from disk
   ///glGenTextures(1, &m_id);
   //unsigned char* data = stbi_load(fname.c_str(), &m_width, &m_height, &m_channels, 0);

   std::array<unsigned char, 3*4*4> data{};
   std::fill(begin(data), end(data), '1');
   data.back() = '\n';
   std::cout << data.data() << std::endl;
   
   m_width = 4;
   m_height = 4;
   m_channels = 3;
   std::cout << "Width: " << m_width << std::endl;
   std::cout << "Height: " << m_height << std::endl;
   std::cout << "Channels: " << m_channels << std::endl;

   if (data.data() == nullptr)
   {
      std::stringstream msg{"Failed to read texture: "};
      msg << fname;
      throw std::runtime_error(msg.str());
   }

   // Load texture to graphics card
   glActiveTexture(GL_TEXTURE0);
   glGenTextures(1, &m_id);
   bind();
   glTexImage2D(
         GL_TEXTURE_2D,
         0,
         GL_RGB,
         m_width, 
         m_height,
         0,
         GL_RGB,
         GL_UNSIGNED_BYTE,
         data.data());

   // Free memory
   //std::puts("Freeing Memory");
   //stbi_image_free(data);
   //std::puts("Freed Memory");
   
   // Set texture wrapping
   //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
   //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
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
