#ifdef __WIN32__
# define SDL_MAIN_HANDLED
#endif

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <stdlib.h>

#include "types.h"
#include "log.h"
#include "shader.h"
#include "vectors.h"
#include "sdltime.h"
#include "solarsystem.h"

#define TPS_DEFAULT 60

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
	f64				tps_dt;
	int				tps;
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
	solarsystem_t	solarsys;
	sdltime_t		time;
	shader_t		shader_default;
	state_t			state;
	f64				accumulated_time;

	state = (state_t){0};
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
	time = time_init();
	shader_default = shader_null;
	shader_default = shader_create("res/shaders/default.vert", "res/shaders/default.frag");
	assert(shader_valid(&shader_default), "failed to create defaultshader");
	solarsys = solarsystem_init();
	state.tps = TPS_DEFAULT;
	state.tps_dt = 1.0 / (f64)state.tps;
	accumulated_time = 0;
	state.running = true;
	while (state.running)
	{
		SDL_Event	ev;

		time_update(&time);
		while (SDL_PollEvent(&ev)) {
			switch (ev.type)
			{
				case (SDL_QUIT):
					state.running = false;
					break ;
			}
		}
		solarsystem_update(&solarsys);
		accumulated_time += time.dt;
		while (accumulated_time >= state.tps_dt && state.tps_dt)
		{
			solarsystem_tick(&solarsys);
			accumulated_time -= state.tps_dt;
		}
		glClear(GL_COLOR_BUFFER_BIT);
		solarsystem_render(&solarsys);
		SDL_GL_SwapWindow(state.window);
	}
	solarsystem_end(&solarsys);
	shader_destroy(&shader_default);
	SDL_GL_DeleteContext(state.glcontext);
	SDL_DestroyWindow(state.window);
	SDL_Quit();
	return (0);
}
