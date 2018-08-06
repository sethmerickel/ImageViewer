#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>

#include "ShaderProgram.h"

#include "Shader.h"

//-----------------------------------------------------------------------------

ShaderProgram::ShaderProgram(
   const std::string& vs_fname,
   const std::string& gs_fname,
   const std::string& fs_fname)
   :m_id(glCreateProgram()),
    m_vs_fname(vs_fname),
    m_gs_fname(gs_fname),
    m_fs_fname(fs_fname)
{
   compileAndLink();
}
   
//-----------------------------------------------------------------------------

ShaderProgram::~ShaderProgram()
{
   glDeleteProgram(m_id);
}

//-----------------------------------------------------------------------------

ShaderProgram::ShaderProgram(ShaderProgram&& sp)
   :m_id(sp.m_id),
    m_vs_fname(sp.m_vs_fname),
    m_gs_fname(sp.m_gs_fname),
    m_fs_fname(sp.m_fs_fname)
{
   sp.m_id = 0;   
}

//-----------------------------------------------------------------------------

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& rhs)
{
   m_vs_fname = rhs.m_vs_fname;
   m_gs_fname = rhs.m_gs_fname;
   m_fs_fname = rhs.m_fs_fname;
   std::swap(m_id, rhs.m_id); 
   return *this;
}

//-----------------------------------------------------------------------------

void
ShaderProgram::attachShader(GLuint shader_id)
{
   glAttachShader(m_id, shader_id);
}

//-----------------------------------------------------------------------------

void 
ShaderProgram::link()
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


void 
ShaderProgram::compileAndLink()
{
   bool link_ok = false;
   if (m_vs_fname.empty() == false)
   {
      Shader shader(ShaderType::VERTEX, m_vs_fname);
      this->attachShader(shader.getId());
      link_ok = true;
   }

   if (m_gs_fname.empty() == false)
   {
      Shader shader(ShaderType::GEOMETRY, m_gs_fname);
      this->attachShader(shader.getId());
      link_ok = true;
   }

   if (m_fs_fname.empty() == false)
   {
      Shader shader(ShaderType::FRAGMENT, m_fs_fname);
      this->attachShader(shader.getId());
      link_ok = true;
   }

   if (link_ok == false)
   {
      std::stringstream msg;
      msg << "Can't construct ShaderProgram. \n";
      msg << "m_vs_fname: " << m_vs_fname << std::endl;
      msg << "m_gs_fname: " << m_gs_fname << std::endl;
      msg << "m_fs_fname: " << m_fs_fname << std::endl;
      throw std::runtime_error{msg.str()};
   }

   // Link the program
   link();
}

//-----------------------------------------------------------------------------

void 
ShaderProgram::use()
{
   glUseProgram(m_id);
}

//-----------------------------------------------------------------------------

void 
ShaderProgram::unUse()
{
   glUseProgram(0);
}

//-----------------------------------------------------------------------------

GLint 
ShaderProgram::attrib(const GLchar* name) const
{
   GLint attrib = glGetAttribLocation(m_id, name);
   if (attrib == -1)
   {
      std::string msg = "Attribute not found: ";
      msg += name;
      throw std::runtime_error(msg);
   }

   return attrib;
}

//-----------------------------------------------------------------------------
