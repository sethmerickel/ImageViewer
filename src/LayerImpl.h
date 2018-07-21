#pragma once

#include "Drawable.hpp"
#include "Layer.h"

class LayerImpl : public Layer
{
public:
   LayerImpl(ShaderProgram&& sp, Drawable&& drawable);

   virtual void draw() override;
   virtual void reload() override;
  
private:
   ShaderProgram m_sp;
   Drawable m_drawable;
};


