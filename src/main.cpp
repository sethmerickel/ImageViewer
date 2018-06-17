#include <iostream>

#include "Window.h"

int main()
{
   try
   {
      Window window(640, 480);
      //Window window(200, 200);
      window.start(); 
   }
   catch (std::exception& e)
   {
      std::cerr << "Exception: " << e.what() << std::endl;
      return -1;
   }
   
   return 0;
}

