#include "Window.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "LayerImpl.h"
#include "Triangle.h"

namespace
{
   //--------------------------------------------------------------------------
   
   void glfwErrorCb(int error, const char* desc)
   {
      std::cerr << "Error: " << desc << std::endl;
   }

   //--------------------------------------------------------------------------
   
   void glfwKeyCb(GLFWwindow* glfw_window, int key, int scancode, int action, int mode)
   {
      if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      {
         glfwSetWindowShouldClose(glfw_window, GL_TRUE);
      }
      else if (key == GLFW_KEY_R && action == GLFW_PRESS)
      {
         Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
         window->updateDrawables();
      }
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
   m_glfw_window = glfwCreateWindow(width, height, "Image Viewer", nullptr, nullptr);
   if (m_glfw_window == nullptr) 
   {
      glfwTerminate();
      throw std::runtime_error("Failed to create GLFW window");
   }

   glfwMakeContextCurrent(m_glfw_window);

   glfwSetWindowUserPointer(m_glfw_window, this);
   glfwSetKeyCallback(m_glfw_window, glfwKeyCb);
   glfwSetFramebufferSizeCallback(m_glfw_window, glfwFramebufferResizeCb);

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

void 
Window::start()
{
   // Add some stuff to draw 
   ShaderProgram sp{"src/Shaders/shader.vs", "", "src/Shaders/shader.fs"};
   Triangle triangle{sp};

   m_layers.emplace_back(
         new LayerImpl{std::move(sp), std::move(triangle)});
            
  
   // Start drawing
   while (drawing())
   {
      draw();
   }
}

//-----------------------------------------------------------------------------

bool 
Window::drawing()
{
   return !glfwWindowShouldClose(m_glfw_window);
}

//-----------------------------------------------------------------------------

void 
Window::draw()
{
   //processInput(m_glfw_window);

   //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
   //glClear(GL_COLOR_BUFFER_BIT);

   for (auto& layer : m_layers)
   {
      layer->draw();
   }

   glfwSwapBuffers(m_glfw_window);

   //glfwWaitEvents();
   glfwPollEvents();
}

//-----------------------------------------------------------------------------

void
Window::updateDrawables()
{
   for(auto& layer : m_layers)
   {
      layer->reload();
   }
}

//-----------------------------------------------------------------------------
