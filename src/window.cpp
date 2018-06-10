#include "Window.h"

#include <iostream>
#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
   mGLFWwindow = glfwCreateWindow(width, height, "Image Viewer", nullptr, nullptr);
   glfwMakeContextCurrent(mGLFWwindow);
   if (mGLFWwindow == nullptr) 
   {
      glfwTerminate();
      throw std::runtime_error("Failed to create GLFW window");
   }

   glfwSetKeyCallback(mGLFWwindow, glfwKeyCb);
   glfwSetFramebufferSizeCallback(mGLFWwindow, glfwFramebufferResizeCb);

   if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
   {
      throw std::runtime_error("Failed to initialize OpenGL context");
   }

   glViewport(0, 0, width, height);
}

//-----------------------------------------------------------------------------

Window::~Window()
{
   glfwTerminate();
}

//-----------------------------------------------------------------------------

bool Window::drawing()
{
   return !glfwWindowShouldClose(mGLFWwindow);
}

//-----------------------------------------------------------------------------

void Window::draw()
{
   glfwPollEvents();

   glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT);
   glfwSwapBuffers(mGLFWwindow);
}

//-----------------------------------------------------------------------------


