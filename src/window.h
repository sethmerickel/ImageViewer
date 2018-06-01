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

   struct DestroyGLFWwindow
   {
      void operator()(GLFWwindow* window);
   };

   std::unique_ptr<GLFWwindow, DestroyGLFWwindow> mGLFWwindow;
};
