#pragma once

#include <vector>
#include "Drawable.hpp"

class GLFWwindow;

class Window
{
public:
   Window(int width, int height);
   ~Window();
   void start();
   bool drawing();
   void draw(); 
   void terminate();

   template <typename DrawableT>
   void addDrawable(const DrawableT& drawable); 

private:
   GLFWwindow* m_GLFWwindow = nullptr; //owns this pointer. Don't delete!
   std::vector<Drawable> m_drawables;
};
