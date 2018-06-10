#include <iostream>

#include "Window.h"

int main()
{
   try
   {
      Window window(640, 480);

      while (window.drawing())
      {
         window.draw();
      }
   }
   catch (std::exception& e)
   {
      std::cerr << "Exception: " << e.what() << std::endl;
      return -1;
   }
   
   return 0;
}

