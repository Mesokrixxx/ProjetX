#ifdef __WIN32__
# define SDL_MAIN_HANDLED
#endif

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <stdlib.h>

#include "types.h"
#include "log.h"
#include "shader.h"
#include "mesh.h"
#include "vectors.h"

#define assert(c, fmt, ...)				\
	do { 								\
		if (!(c)) {						\
			error(fmt, ##__VA_ARGS__);	\
			exit(1);					\
		}								\
	} while (0)

typedef struct state_s {
	SDL_Window		*window;
	SDL_GLContext	glcontext;
	bool			running;
}	state_t;

typedef struct {
	v3	position;
}	vertex_t;

typedef struct {
	v3	position;
	f32	scale;
}	quadinstance_t;

int main(void)
{
	state_t	state;

	assert(!SDL_Init(SDL_INIT_VIDEO), "failed to init sdl video: %s", 
		SDL_GetError());
	state.window = 
		SDL_CreateWindow(
			"ProjetX",
			SDL_WINDOWPOS_CENTERED_DISPLAY(1),
			SDL_WINDOWPOS_CENTERED_DISPLAY(1),
			1080, 720,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	assert(state.window, "failed to create sdl window: %s",
		SDL_GetError());
	state.glcontext = SDL_GL_CreateContext(state.window);
	assert(state.glcontext, "failed to create sdl gl context: %s",
		SDL_GetError());
	assert(glewInit() == GLEW_OK, "failed to init glew");

	shader_t	shader_default = shader_null;
	shader_default = shader_create("res/shaders/default.vert", "res/shaders/default.frag");
	assert(shader_valid(&shader_default), "failed to create defaultshader");

	mesh_t mesh_quad = mesh_null;
	vertex_t quadvertices[] = {
		{ .position = v3_of(0, 1, 0) },
		{ .position = v3_of(1, 1, 0) },
		{ .position = v3_of(1, 0, 0) },
		{ .position = v3_of(0, 0, 0) }
	};
	unsigned short indices[] = {
		2, 1, 0, 3, 2, 0
	};
	mesh_quad = mesh_create(MESH_INSTANCED_ELEMENT);
	mesh_setup(&mesh_quad, 
		(meshsetup_t){
			.vertices = {
				.data = quadvertices,
				.count = sizeof(quadvertices) / sizeof(vertex_t),
				.unitsize = sizeof(vertex_t),
				.usage = GL_STATIC_DRAW,
				.attributes_count = 1,
				.attributes = (meshattributes_t[]){
					{
						.gltype = GL_FLOAT,
						.size = 3,
					}
				}
			},
			.elements = {
				.count = sizeof(indices) / sizeof(unsigned short),
				.data = indices,
				.usage = GL_STATIC_DRAW,
				.totlsize = sizeof(indices),
				.gltype = GL_UNSIGNED_SHORT
			},
			.instances = {
				.capacity = 1,
				.unitsize = sizeof(quadinstance_t),
				.usage = GL_STREAM_DRAW,
				.attributes_count = 2,
				.attributes = (meshattributes_t[]){
					{
						.gltype = GL_FLOAT,
						.size = 3
					},
					{
						.gltype = GL_FLOAT,
						.size = 1,
						.offset = offsetof(quadinstance_t, scale)
					}
				}
			}
		});
	assert(mesh_valid(&mesh_quad), "failed to create quad mesh");
	mesh_append(&mesh_quad, 1, &(quadinstance_t){ .position = v3_of(0, 0, 0), .scale = 0.5f});

	state.running = true;
	while (state.running)
	{
		SDL_Event	ev;

		while (SDL_PollEvent(&ev)) {
			switch (ev.type)
			{
				case (SDL_QUIT):
					state.running = false;
					break ;
			}
		}
		glClear(GL_COLOR_BUFFER_BIT);
		shader_bind(&shader_default);
		mesh_draw(&mesh_quad, 0, GL_TRIANGLES);
		SDL_GL_SwapWindow(state.window);
	}
	mesh_destroy(&mesh_quad);
	shader_destroy(&shader_default);
	SDL_GL_DeleteContext(state.glcontext);
	SDL_DestroyWindow(state.window);
	SDL_Quit();
	return (0);
}
