#include "r_main.h"
#include "m_log.h"
#include "m_misc.h"

void SWindow::Init(short width, short height, const char* title)
{
	if (!glfwInit())
	{
		M_Error("failed to init glfw!\n");
		exit(1);
	}
	this->width = width, this->height = height;
	if (title)
		M_strncpy(this->title, title, asizeof(this->title));
	else
		M_strcpy(this->title, "Window");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if ((this->window = glfwCreateWindow(this->width, this->height, this->title, NULL, NULL)) == NULL)
	{
		M_Error("failed to create window (width %i, height %i, title %s)\n", this->width, this->height, this->title);
		exit(1);
	}
	glfwMakeContextCurrent(this->window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		M_Error("failed to load glad!\n");
		exit(1);
	}

	glfwSetWindowSizeCallback(this->window, (GLFWwindowsizefun)R_WindowSizeChangeCallback);
	R_WindowSizeChangeCallback(this->window, this->width, this->height);

	glClearColor(.15f, .3f, .2f, .0f);
	glClearDepth(1.f);
	glClearStencil(255);
}

void SWindow::Update()
{
	glfwSwapBuffers(this->window);
}

bool SWindow::ShouldClose()
{
	return glfwWindowShouldClose(this->window);
}

void R_WindowSizeChangeCallback(GLFWwindow* window, int new_width, int new_height)
{
	glViewport(0, 0, new_width, new_height);
}