#include "Layer.h"

#include <cmath>

//-----------------------------------------------------------------------------

Layer::Layer(ShaderProgram&& sp, Drawable&& drawable)
   :m_sp(std::move(sp)),
   m_drawable(std::move(drawable))
{

}

//-----------------------------------------------------------------------------

void 
Layer::setShaderProgram(ShaderProgram&& sp)
{
   m_sp = std::move(sp);
}

//-----------------------------------------------------------------------------

void
draw(Layer& layer)
{
   layer.m_sp.use();
   GLfloat t = glfwGetTime();
   GLfloat grn = (std::sin(t) / 2.0) + 0.5;
   GLint color_loc = glGetUniformLocation(layer.m_sp.getId(), "color");
   glUniform4f(color_loc, 0.0f, grn, 0.1f, 1.0f);
   
   layer.m_drawable.draw();
   layer.m_sp.unUse(); 
}

//-----------------------------------------------------------------------------
void
update(Layer& layer)
{
   ShaderProgram new_sp(
         layer.m_sp.getVsFname(),
         layer.m_sp.getGsFname(),
         layer.m_sp.getFsFname());

   layer.m_sp = std::move(new_sp);
}

