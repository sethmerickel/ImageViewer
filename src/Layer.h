#pragma once

#include "Drawable.hpp"
#include "ShaderProgram.h"

class Layer
{
public:
   Layer(ShaderProgram&& sp, Drawable&& drawable);

   void setShaderProgram(ShaderProgram&& sp);

   friend void draw(Layer& layer);
   
   friend void update(Layer& layer);

private:
   ShaderProgram m_sp;
   Drawable m_drawable;
};


