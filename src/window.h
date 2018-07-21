#pragma once

#include <memory>
#include <vector>

class GLFWwindow;
class Layer;

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
   std::vector<std::unique_ptr<Layer>> m_layers;
};
