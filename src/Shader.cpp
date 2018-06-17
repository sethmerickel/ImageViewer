#include "Shader.h"

#include <stdexcept>
#include <fstream>
#include <iostream>
#include <sstream>

//-----------------------------------------------------------------------------

Shader::Shader(ShaderType type)
   :m_type(type)
{
   if (type == ShaderType::VERTEX)
      m_id = glCreateShader(GL_VERTEX_SHADER);
   else if (type == ShaderType::GEOMETRY)
      m_id = glCreateShader(GL_GEOMETRY_SHADER);
   else if (type == ShaderType::FRAGMENT)
      m_id = glCreateShader(GL_FRAGMENT_SHADER);
   else
      throw std::runtime_error("Unsupported ShaderType");
}

//-----------------------------------------------------------------------------

Shader::~Shader()
{
   glDeleteShader(m_id);
}

//-----------------------------------------------------------------------------

Shader::Shader(Shader&& shader)
{
   m_type = shader.m_type;
   m_id = shader.m_id;
   shader.m_id = 0; // 0 is silently ignored by OpenGl
}


Shader& 
Shader::operator=(Shader&& shader)
{
   m_type = shader.m_type;
   m_id = shader.m_id;
   shader.m_id = 0; // 0 is silently ignored by OpenGl
}

//-----------------------------------------------------------------------------

void 
Shader::compile(const std::string& source)
{
   const GLchar* source_ptr = source.c_str();
   glShaderSource(m_id, 1, &source_ptr, nullptr);
   glCompileShader(m_id);

   // Check compile status
   GLint status;
   glGetShaderiv(m_id, GL_COMPILE_STATUS, &status);
   if (status != GL_TRUE)
   {
       GLsizei log_length = 0;
       GLchar message[1024];
       glGetShaderInfoLog(m_id, 1024, nullptr, message);
       throw std::runtime_error(message);
   }
}

//-----------------------------------------------------------------------------

std::string 
Shader::readFromFile(const std::string& fname)
{
   std::ifstream ifs(fname);
   std::stringstream buffer;
   buffer << ifs.rdbuf();
   return buffer.str(); 
}

//-----------------------------------------------------------------------------
