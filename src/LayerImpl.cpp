#include "LayerImpl.h"

//------------------------------------------------------------------------------

LayerImpl::LayerImpl(ShaderProgram&& sp, Drawable&& drawable)
  :m_sp(std::move(sp)),
   m_drawable(std::move(drawable))
{

}

//------------------------------------------------------------------------------

void
LayerImpl::reload()
{
   ShaderProgram sp {m_sp.getVsFname(), m_sp.getGsFname(), m_sp.getFsFname()};
   m_sp = std::move(sp);
}

//------------------------------------------------------------------------------

void
LayerImpl::draw()
{
   //m_sp.use();
   //GLfloat t = glfwGetTime();
   //GLfloat grn = (std::sin(t) / 2.0) + 0.5;
   //GLint color_loc = glGetUniformLocation(layer.m_sp.getId(), "color");
   //glUniform4f(color_loc, 0.0f, grn, 0.1f, 1.0f);
   // int loc = glGetUniformLocation(layer.m_sp.getId(), "our_texture");
   // if( loc >= 0 )
   //     glUniform1i(loc, 0);
   // else
   //    throw std::runtime_error("Can't get sampler uniform location");

   //
   m_drawable.draw(m_sp);
   //m_sp.unUse(); 

}

