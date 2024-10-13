#include "r_main.h"
#include "m_log.h"

void SShader::Init()
{
   this->program = glCreateProgram();
}

void SShader::AddShader(int type, const char* code)
{
   unsigned int shader = glCreateShader(type);
   glShaderSource(shader, 1, &code, NULL);
   glCompileShader(shader);

   if (!this->CheckShaderValidity(shader))
   {
      glDeleteShader(shader);
      return;
   }
   if (this->shader_count < 7)
   {
      this->shaders[this->shader_count++] = shader;
      glAttachShader(this->program, shader);
   }
}

void SShader::LinkShader()
{
   glLinkProgram(this->program);
 
   if (!this->CheckProgramValidity())
   {
      glDeleteProgram(this->program);
      this->program = glCreateProgram();
   }
}

bool SShader::CheckProgramValidity()
{
   int success;
   char log[1024];
   glGetProgramiv(this->program, GL_LINK_STATUS, &success);

   if (!success)
   {
      glGetProgramInfoLog(this->program, 1024, NULL, log);
      M_Error("failed to link program! providing log\n%s\n", log);
      return false;
   }
   return true;
}

bool SShader::CheckShaderValidity(unsigned int shader)
{
   int success;
   char log[1024];
   glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

   if (!success)
   {
      glGetShaderInfoLog(shader, 1024, NULL, log);
      M_Error("failed to compile shader! providing log\n%s\n", log);
      return false;
   }
   return true;
}