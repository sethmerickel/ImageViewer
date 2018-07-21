#include <cmath>
#include <stdexcept>
#include <iostream>
#include <string>

#include "Triangle.h"
#include "Shader.h"
#include "Texture.h"
//-----------------------------------------------------------------------------

Triangle::Triangle()
   :m_texture("src/textures/wall.jpg")
{
   // Triangle vertices
   //GLfloat vertices[] = {
   //   -0.7f,  0.7f, 0.0f, 1.0f, 0.0f, 0.0f, // Top Left 
   //   -0.7f, -0.7f, 0.0f, 0.0f, 1.0f, 0.0f, // Bottom Left 
   //    0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 1.0f, // Bottom Right
   //    0.7f,  0.7f, 0.0f, 0.3f, 0.3f, 0.3f  // Top Right
   //};
   //
  
   float vertices[] = {
       // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
       -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
   };
   
   //GLuint indices[] = {
   //   //0, 1, 2  // Tri 1
   //   1, 2, 0  // Tri 1
   //};
   //
   // Configure Texture
   m_texture.bind();
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   m_texture.unBind();

   // Generate ids 
   glGenVertexArrays(1, &m_vao_id);
   glGenBuffers(1, &m_vbo_id);
   //glGenBuffers(1, &m_ebo_id);

   // Set up vertex data 
   glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 

   // Set up index data
   //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo_id);
   //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

   // Set up VAO
   glBindVertexArray(m_vao_id);
   glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);
   //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo_id);
   
   // Vertex position location = 0
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (void*)0);
   glEnableVertexAttribArray(0);
 
   // Color location = 1
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
   glEnableVertexAttribArray(1);
 
   // Texture location = 1
   glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (void*)(6*sizeof(GLfloat)));
   glEnableVertexAttribArray(2);

   // Unbind VAO
   glBindVertexArray(0);
  
   // Clean up
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//-----------------------------------------------------------------------------

void draw(Triangle& triangle, ShaderProgram& sp)
{
   triangle.m_texture.bind();
   glBindVertexArray(triangle.m_vao_id);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
   glBindVertexArray(0);
   triangle.m_texture.unBind();
}

//-----------------------------------------------------------------------------

void 
update(Triangle& triangle)
{
   // Nothing to update 
}

//-----------------------------------------------------------------------------

