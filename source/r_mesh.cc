#include "r_main.h"
#include "m_misc.h"
#include "alloc.h"

void SMesh::Init()
{
   glGenVertexArrays(1, &this->vao);
   this->buffer = (SBuffer*)A_ZeroAlloc(sizeof(SBuffer));
   this->buffer->CreateBuffer();
}

void SMesh::BufferQuad()
{
   if (!this->vao && !this->buffer)
      this->Init();

   SVertexAttribute attributes[] = {
      {0, 3, GL_FLOAT, false, 5 * sizeof(float), 0},
      {0, 3, GL_FLOAT, false, 5 * sizeof(float), 3 * sizeof(float)},
   };
   this->buffer->Buffer(quad_vertices, sizeof(quad_vertices[0]), asizeof(quad_vertices), GL_STATIC_DRAW, GL_ARRAY_BUFFER, attributes, 2, this->vao);
}