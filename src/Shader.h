#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader
{
public:
   
   enum TypeFlag : char
   { 
      VERT = 0,
      FRAG = 1 << 0,
      GEOM = 1 << 1
   };

   Shader(
      const std::string& vs_fname, 
      const std::string& gs_fname,
      const std::string& fs_fname);

   void compile(TypeFlag flag);

private:
   std::string m_vs_str;
   std::string m_gs_str;
   std::string m_fs_str;
   GLuint m_vs_id;
   GLuint m_gs_id;
   GLuint m_fs_id;
};
