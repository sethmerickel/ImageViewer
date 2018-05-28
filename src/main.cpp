#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void glfw_error_cb(int error, const char* desc)
{
   std::cerr << "Error: " << desc << std::endl;
}

void glfw_key_cb(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    std::cout << key << std::endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int WIDTH = 640;
int HEIGHT = 480; 

int main()
{
   if (!glfwInit()) return -1;

   // Set error handler
   glfwSetErrorCallback(glfw_error_cb);

   // Create an OpenGL 4.1 window.  These hints are special for Mac 
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Image Viewer", nullptr, nullptr);
   glfwMakeContextCurrent(window);
   if (window == nullptr) 
   {
      std::cerr << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      return -1;
   }

   glfwSetKeyCallback(window, glfw_key_cb);

   if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
   {
      std::cout << "Failed to initialize OpenGL context" << std::endl;
      return -1;
   }

   glViewport(0, 0, WIDTH, HEIGHT);

   while (!glfwWindowShouldClose(window))
   {
      glfwPollEvents();

      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
      glfwSwapBuffers(window);
   }

   glfwTerminate();
   return 0;
}

