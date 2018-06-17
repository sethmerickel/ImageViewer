#include <stdexcept>

#include "ShaderProgram.h"

//-----------------------------------------------------------------------------

ShaderProgram::ShaderProgram()
   :m_id(glCreateProgram())
{

}
   
//-----------------------------------------------------------------------------

ShaderProgram::~ShaderProgram()
{
   glDeleteProgram(m_id);
}

//-----------------------------------------------------------------------------

ShaderProgram::ShaderProgram(ShaderProgram&& shader_program)
   :m_id(shader_program.m_id)
{
   shader_program.m_id = 0;   
}

//-----------------------------------------------------------------------------

void ShaderProgram::attachShader(GLuint shader_id)
{
   glAttachShader(m_id, shader_id);
}

//-----------------------------------------------------------------------------

//void ShaderProgram::detachShader(ShaderType shader_type)
//{
//   if (shader_type == ShaderType::VERTEX)
//   {
//      glDetachShader(m_id, m_vs.getId());
//   }
//   else if (shader_type == ShaderType::GEOMETRY)
//   {
//      glDetachShader(m_id, m_gs.getId());
//   }
//   else if (shader_type == ShaderType::FRAGMENT)
//   {
//      glDetachShader(m_id, m_fs.getId());
//   }
//}

//-----------------------------------------------------------------------------

void ShaderProgram::link()
{
   glLinkProgram(m_id);

   // Check link status
   GLint status;
   glGetProgramiv(m_id, GL_LINK_STATUS, &status);
   if (status != GL_TRUE)
   {
      GLsizei log_length = 0;
      GLchar message[1024];
      glGetProgramInfoLog(m_id, 1024, nullptr, message);
      throw std::runtime_error(message);
   }
}

//-----------------------------------------------------------------------------

void ShaderProgram::use()
{
   glUseProgram(m_id);
}

//-----------------------------------------------------------------------------

void ShaderProgram::disable()
{

}

