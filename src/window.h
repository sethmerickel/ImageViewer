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
   void updateDrawables();

private:
   GLFWwindow* m_glfw_window = nullptr; //owns this pointer. Don't delete!
   std::vector<Drawable> m_drawables;
};
