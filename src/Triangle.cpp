#include <iostream>
#include <string>

#include "Shader.h"
#include "Triangle.h"

//-----------------------------------------------------------------------------

Triangle::Triangle()
{
   std::string vs_source = 
      "#version 410 core\n"
      "layout (location = 0) in vec3 aPos;\n"
      "void main()\n"
      "{\n"
      "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
      "}\n";

   //std::cout << "VERTEX SOURCE: " << std::endl;
   //std::cout << vs_source << std::endl;

   Shader vs(ShaderType::VERTEX);
   vs.compile(vs_source);
   m_sp.attachShader(vs.getId());

   std::string fs_source = 
      "#version 410 core\n"
      "out vec4 FragColor;\n"
      "void main()\n"
      "{\n"
      "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
      "}\n";

   //std::cout << "FRAGMENT SOURCE: " << std::endl;
   //std::cout << vs_source << std::endl;

   Shader fs(ShaderType::FRAGMENT);
   fs.compile(fs_source);
   m_sp.attachShader(fs.getId());
   
   // Link shaders into a shader program
   m_sp.link();

   
   // Triangle vertices
   float vertices[] = {
      -0.5f, -0.5f, 0.0f,
       0.5f, -0.5f, 0.0f,
       0.0f,  0.5f, 0.0f
   };

   // Generate ids 
   glGenVertexArrays(1, &m_vao_id);
   glGenBuffers(1, &m_vbo_id);
   
   // Set up vertex data 
   glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 
   
   // Set up VAO
   glBindVertexArray(m_vao_id);
  
   // Vertex position //vertex attribut location = 0
   glEnableVertexAttribArray(0);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

   // Unbind VAO
   glBindVertexArray(0);
}

//-----------------------------------------------------------------------------

void draw(Triangle& triangle)
{
   triangle.m_sp.use();
   glBindVertexArray(triangle.m_vao_id);
   glDrawArrays(GL_TRIANGLES, 0, 3);
   glBindVertexArray(0);
}

//-----------------------------------------------------------------------------

