#include <cmath>
#include <stdexcept>
#include <iostream>
#include <string>

#include "Triangle.h"
#include "ShaderProgram.h"
#include "Texture.h"
//-----------------------------------------------------------------------------

Triangle::Triangle(const ShaderProgram& sp)
   :m_texture("src/textures/wall.jpg")
{
   glGenVertexArrays(1, &m_vao_id);
   glBindVertexArray(m_vao_id);

   glGenBuffers(1, &m_vbo_id);
   glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);
   
   GLfloat vertexData[] = {
      //  X     Y     Z       U     V
      0.0f, 0.8f, 0.0f,   0.5f, 0.0f,
     -0.8f,-0.8f, 0.0f,   0.0f, 1.0f,
      0.8f,-0.8f, 0.0f,   1.0f, 1.0f,
   };

   glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW); 
   
   glEnableVertexAttribArray(sp.attrib("vert"));
   glVertexAttribPointer(sp.attrib("vert"), 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), nullptr);

   glEnableVertexAttribArray(sp.attrib("vertTexCoord"));
   glVertexAttribPointer(sp.attrib("vertTexCoord"), 2, GL_FLOAT, GL_TRUE, 5*sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));

   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindVertexArray(0); 
}

//-----------------------------------------------------------------------------

Triangle::Triangle(Triangle&& tri)
   :m_vbo_id(tri.m_vbo_id),
    m_vao_id(tri.m_vao_id),
    m_ebo_id(tri.m_ebo_id),
    m_texture(std::move(tri.m_texture))
{
}

//-----------------------------------------------------------------------------

Triangle& Triangle::operator=(Triangle&& rhs)
{
   std::swap(m_vbo_id, rhs.m_vbo_id); 
   std::swap(m_vao_id, rhs.m_vao_id);
   std::swap(m_ebo_id, rhs.m_ebo_id);
   std::swap(m_texture, rhs.m_texture);
}

//-----------------------------------------------------------------------------

void draw(Triangle& triangle, ShaderProgram& sp)
{
   glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT);
  
   sp.use();
   
   // Set sampler uniform
   GLint uni_loc = glGetUniformLocation(sp.getId(), "tex");
   glUniform1i(uni_loc, 0); // TODO: Texture class needs to manage this

   glBindVertexArray(triangle.m_vao_id);

   glActiveTexture(GL_TEXTURE0); // TODO: Texture class needs to manage this
   triangle.m_texture.bind();

   //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glDrawArrays(GL_TRIANGLES, 0, 3);
   
   glBindVertexArray(0);
   triangle.m_texture.unBind();
   sp.unUse();
}

//-----------------------------------------------------------------------------

void 
update(Triangle& triangle)
{
   // Nothing to update 
}

//-----------------------------------------------------------------------------

