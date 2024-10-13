#ifndef __R_MAIN
#define __R_MAIN

#include <cstdlib>
#include <cstdint>

#include "glad.h"
#include <GLFW/glfw3.h>
#include <glm.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec2 uv;
};

static float quad_vertices[] = {
	  0.5f,  0.5f, 0.0f,		1.f, 0.f,	// top right
	  0.5f, -0.5f, 0.0f,		1.f, 1.f,	// bottom right
	 -0.5f, -0.5f, 0.0f,		0.f, 1.f,	// bottom left
	 -0.5f,  0.5f, 0.0f,		0.f, 0.f		// top left 
};
static unsigned int quad_indices[] = {
	 0, 1, 3,   // first triangle
	 1, 2, 3    // second triangle
};

struct SWindow
{
	GLFWwindow* window;
	short width, height;
	char title[32];

	void Init(short width, short height, const char *title = NULL);
	void Update();

	bool ShouldClose();
};

struct SVertexAttribute
{
	int index;
	int size;
	int type;
	bool normalized;
	long stride;
	long offset;
};
struct SBuffer
{
	unsigned int ID;

	void CreateBuffer();
	void DestroyBuffer();

	void Buffer(void *data, int element_size, int amount, int usage, int target,
		SVertexAttribute *attributes = NULL, int attr_amount = 0, int vao = 0);
};
struct SMesh
{
	unsigned int vao;
	SBuffer* buffer, *indices_buffer;

	void Init();
	void BufferQuad();
};

void R_WindowSizeChangeCallback(GLFWwindow* window, int new_width, int new_height);


#endif