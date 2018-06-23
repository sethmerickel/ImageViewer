#include "Window.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Triangle.h"

namespace
{
   //--------------------------------------------------------------------------
   
   void glfwErrorCb(int error, const char* desc)
   {
      std::cerr << "Error: " << desc << std::endl;
   }

   //--------------------------------------------------------------------------
   
   void glfwKeyCb(GLFWwindow* window, int key, int scancode, int action, int mode)
   {
       std::cout << key << std::endl;
       if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
           glfwSetWindowShouldClose(window, GL_TRUE);
   }

   //--------------------------------------------------------------------------
   
   void glfwFramebufferResizeCb(GLFWwindow* window, int width, int height)
   {
      glViewport(0, 0, width, height);
   }

   void processInput(GLFWwindow* window)
   {
      if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      {
         glfwSetWindowShouldClose(window, true);
      }
   }
}

//-----------------------------------------------------------------------------

Window::Window(int width, int height)
{
   if (!glfwInit()) 
      throw std::runtime_error("Failed to initialize glfw");

   // Set error handler
   glfwSetErrorCallback(glfwErrorCb);

   // Create an OpenGL 4.1 window.  These hints are special for Mac 
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   m_GLFWwindow = glfwCreateWindow(width, height, "Image Viewer", nullptr, nullptr);
   if (m_GLFWwindow == nullptr) 
   {
      glfwTerminate();
      throw std::runtime_error("Failed to create GLFW window");
   }

   glfwMakeContextCurrent(m_GLFWwindow);

   glfwSetKeyCallback(m_GLFWwindow, glfwKeyCb);
   glfwSetFramebufferSizeCallback(m_GLFWwindow, glfwFramebufferResizeCb);

   if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
   {
      throw std::runtime_error("Failed to initialize OpenGL context");
   }
  
   // Width/height need to be doubled for glViewport.  Don't know why...
   width *= 2;
   height *= 2;
   glViewport(0, 0, width, height);
}

//-----------------------------------------------------------------------------

Window::~Window()
{
   glfwTerminate();
}

//-----------------------------------------------------------------------------

void Window::start()
{
   // Add some stuff to draw 
   m_drawables.emplace_back(Triangle{});
  
   // Start drawing
   while (drawing())
   {
      draw();
   }
}

//-----------------------------------------------------------------------------

bool Window::drawing()
{
   return !glfwWindowShouldClose(m_GLFWwindow);
}

//-----------------------------------------------------------------------------

void Window::draw()
{
   processInput(m_GLFWwindow);

   glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT);

   for (auto& drawable : m_drawables)
   {
      drawable.draw();
   }

   glfwSwapBuffers(m_GLFWwindow);

   glfwWaitEvents();
}

//-----------------------------------------------------------------------------


