#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

enum class ShaderType : char
{
   VERTEX = 0,
   FRAGMENT,
   GEOMETRY
};

class Shader
{
public:
   Shader(ShaderType type);

   // Move only
   Shader(const Shader&) = delete;

   // Move only
   Shader& operator=(const Shader&) = delete;

   Shader(Shader&& shader);

   Shader& operator=(Shader&& shader);
   
   ~Shader();

   void compile(const std::string& source);

   GLuint getId() { return m_id; }
   
   ShaderType getShaderType() { return m_type; }

   static std::string readFromFile(const std::string& fname);

private:
   std::string m_source; 
   GLuint m_id;
   ShaderType m_type;
};
