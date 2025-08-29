#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <stdbool.h>

#define ASSERT(c, fmt, ...) 							\
	do {												\
		if (!(c))										\
		{												\
			fprintf(stderr, fmt "\n", ##__VA_ARGS__);	\
			exit(1);									\
		}												\
	} while (0)

typedef struct state_s {
	SDL_Window		*window;
	SDL_GLContext	glcontext;
	bool			running;
}	state_t;

int main(void)
{
	state_t	game;

	ASSERT(!SDL_Init(SDL_INIT_VIDEO),
		"failed to init sdl: %s", SDL_GetError());
	game.window = 
		SDL_CreateWindow(
			"ProjetX",
			SDL_WINDOWPOS_CENTERED_DISPLAY(1), SDL_WINDOWPOS_CENTERED_DISPLAY(1),
			1080, 720,
			SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	ASSERT(game.window, 
		"failed to create window: %s", SDL_GetError());
	game.glcontext = SDL_GL_CreateContext(game.window);
	ASSERT(game.glcontext, 
		"failed to create context: %s", SDL_GetError());
	ASSERT(glewInit() == GLEW_OK, 
		"failed to init glew");
	game.running = true;
	while (game.running)
	{
		SDL_Event	ev;

		while (SDL_PollEvent(&ev))
		{
			switch (ev.type)
			{
				case (SDL_QUIT):
					game.running = false;
					break ;
			}
		}
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(game.window);
	}
	SDL_GL_DeleteContext(game.glcontext);
	SDL_DestroyWindow(game.window);
	SDL_Quit();
	return 0;
}
