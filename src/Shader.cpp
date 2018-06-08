#include "Shader.h"

#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace
{
   //---------------------------------------------------------------------------

   std::string readFile(const std::string& s_fname)
   {
      std::ifstream ifs(s_fname);
      std::stringstream buffer;
      buffer << ifs.rdbuf();
      return buffer.str();
   }

   //---------------------------------------------------------------------------
   
   bool shaderIdIsValid(GLuint id)
   {
      return id != GLuint(-1);
   }

   //---------------------------------------------------------------------------
   
   void compileShader(GLuint id, const std::string& source)
   {
      const GLchar* sources = source.c_str();
      glShaderSource(id, 1, &sources, nullptr);
      glCompileShader(id);
      GLint compiled;
      glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);
      if (compiled != GL_TRUE)
      {
          GLsizei log_length = 0;
          GLchar message[1024];
          glGetShaderInfoLog(id, 1024, &log_length, message);
          throw std::runtime_error(message);
      }
   }
}

//-----------------------------------------------------------------------------

Shader::Shader(
   const std::string& vs_fname, 
   const std::string& gs_fname,
   const std::string& fs_fname)
  :m_vs_str(),
   m_gs_str(),
   m_fs_str(),
   m_vs_id(-1), // wrap
   m_gs_id(-1), // wrap
   m_fs_id(-1)  // wrap
{
   auto throw_if_read_file_error = [](
         const std::string& fname,
         const std::string& shader_str) -> void
   {
      if (shader_str.empty() == true)
      {
         std::stringstream msg; 
         msg << fname;
         msg << " -> invalid shader file";
         throw std::invalid_argument(msg.str());
      }
   };
   
   if (vs_fname.empty() == false)
   {
      m_vs_str = readFile(vs_fname);
      throw_if_read_file_error(vs_fname, m_vs_str);
      m_vs_id = glCreateShader(GL_VERTEX_SHADER);
   }
   
   if (gs_fname.empty() == false)
   {
      m_gs_str = readFile(gs_fname); 
      throw_if_read_file_error(gs_fname, m_gs_str);
      m_gs_id = glCreateShader(GL_GEOMETRY_SHADER);
   }

   if (fs_fname.empty() == false) 
   {
      m_fs_str = readFile(fs_fname);
      throw_if_read_file_error(fs_fname, m_fs_str);
      m_fs_id = glCreateShader(GL_FRAGMENT_SHADER);
   }
}

//-----------------------------------------------------------------------------

void Shader::compile(Shader::TypeFlag flag)
{
   if ((flag & VERT) && shaderIdIsValid(m_vs_id))
   {
      compileShader(m_vs_id, m_vs_str);
   }
  
   if ((flag & GEOM) && shaderIdIsValid(m_gs_id))
   {
      compileShader(m_gs_id, m_gs_str);
   }
  
   if ((flag & FRAG) && shaderIdIsValid(m_fs_id))
   {
      compileShader(m_fs_id, m_fs_str);
   }
}

//-----------------------------------------------------------------------------
