#ifdef __WIN32__
# define SDL_MAIN_HANDLED
#endif

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <stdlib.h>

#include "types.h"
#include "log.h"
#include "shader.h"

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
		SDL_GL_SwapWindow(state.window);
	}

	SDL_GL_DeleteContext(state.glcontext);
	SDL_DestroyWindow(state.window);
	SDL_Quit();
	return (0);
}
