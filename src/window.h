#pragma once

#include <memory>


class GLFWwindow;


class Window
{
public:
   Window(int width, int height);
   ~Window();
   bool drawing();
   void draw();
   void terminate();

private:

   GLFWwindow* mGLFWwindow = nullptr; //owns this pointer. Don't delete!
};
