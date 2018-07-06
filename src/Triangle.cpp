#include <cmath>
#include <iostream>
#include <string>

#include "Shader.h"
#include "Triangle.h"

//-----------------------------------------------------------------------------

Triangle::Triangle()
{
   // Triangle vertices
   GLfloat vertices[] = {
      -0.7f,  0.7f, 0.0f, // Top Left 
      -0.7f, -0.7f, 0.0f, // Bottom Left 
       0.7f, -0.7f, 0.0f, // Bottom Right
       0.7f,  0.7f, 0.0f  // Top Right
   };

   GLuint indices[] = {
      0, 3, 2, // Tri 1
      0, 1, 2  // Tri 2
   };

   // Generate ids 
   glGenVertexArrays(1, &m_vao_id);
   glGenBuffers(1, &m_vbo_id);
   glGenBuffers(1, &m_ebo_id);

   // Set up vertex data 
   glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 

   // Set up index data
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo_id);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

   // Set up VAO
   glBindVertexArray(m_vao_id);
   glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo_id);
   
   // Vertex position //vertex attribut location = 0
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);
   glEnableVertexAttribArray(0);

   // Unbind VAO
   glBindVertexArray(0);
  
   // Clean up
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//-----------------------------------------------------------------------------

void draw(Triangle& triangle)
{
   glBindVertexArray(triangle.m_vao_id);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
   glBindVertexArray(0);
}

//-----------------------------------------------------------------------------

void 
update(Triangle& triangle)
{
   // Nothing to update 
}

//-----------------------------------------------------------------------------

