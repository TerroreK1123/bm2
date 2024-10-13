#include <cstdio>
#include <cstdlib>
#include <gameasm.h>

#include "r_main.h"
#include "m_misc.h"
#include "alloc.h"

SWindow* game_window;
double deltaTime = 0.0;
int maxFps = 60;

int main(int argc, char** argv)
{
	do_alloc_debug = true;
	game_window = (SWindow*) A_ZeroAlloc(sizeof(SWindow));
	game_window->Init(1024, 768);

	SShader* shader = (SShader*)A_ZeroAlloc(sizeof(SShader));
	const unsigned char* frag_source = M_ReadFile("shaders/generic.frag");
	const unsigned char* vert_source = M_ReadFile("shaders/generic.vert");
	shader->AddShader(GL_FRAGMENT_SHADER, (const char*)frag_source);
	shader->AddShader(GL_VERTEX_SHADER, (const char*)vert_source);
	shader->LinkShader();

	SMesh* mesh = (SMesh*)A_ZeroAlloc(sizeof(SMesh));
	mesh->BufferQuad();

	double last_update_time = 0.0;
	double last_frame_time = 0.0;
	while (!game_window->ShouldClose())
	{
		double nowTime = glfwGetTime();
		deltaTime = nowTime - last_update_time;

		glfwPollEvents();
		if ((nowTime - last_frame_time) >= (1.0 / maxFps))
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			glUseProgram(shader->program);
			glBindVertexArray(mesh->vao);
			glDrawElements(GL_TRIANGLES, 4, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			glUseProgram(0);
			
			game_window->Update();
			last_frame_time = nowTime;
		}
		last_update_time = nowTime;
	}

	A_WipeDiary();
	return 0;
}