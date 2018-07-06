#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class ShaderProgram
{
public:
   
   // Create shader program from file paths.  Empty strings are ignored
   ShaderProgram(
         const std::string& vs_fname, 
         const std::string& gs_fname, 
         const std::string& fs_fname); 
   
   ~ShaderProgram();

   ShaderProgram(ShaderProgram&& shader_program);

   ShaderProgram& operator=(ShaderProgram&& sp);

   // Non copyable
   ShaderProgram(const ShaderProgram&) = delete;

   // Non copyable
   ShaderProgram& operator=(const ShaderProgram&) = delete;

   void compileAndLink();

   void use();

   void unUse();

   GLuint getId() { return m_id; }

   std::string getVsFname() const { return m_vs_fname; }
   std::string getGsFname() const { return m_gs_fname; };
   std::string getFsFname() const { return m_fs_fname; };

private:
   
   void attachShader(GLuint shader_id);
   void link();

   std::string m_vs_fname;
   std::string m_gs_fname;
   std::string m_fs_fname;

   GLuint m_id;
};
