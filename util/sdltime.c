#include "sdltime.h"
#include <SDL2/SDL_timer.h>
#include "check.h"

static u64	gfreq;

sdltime_t	time_init(void)
{
	sdltime_t	t = sdltime_null;

	if (!gfreq)
		gfreq = SDL_GetPerformanceFrequency();
	t.freq = gfreq;
	return t;
}

void	time_update(sdltime_t *time)
{
	u64			now, diff, diff_dt;

	checkarg(time);
	if (time->freq != gfreq && gfreq)
	{
		error("time_init must be called before time_update");
		return ;
	}
	now = SDL_GetPerformanceCounter();
	if (!time->start)
	{
		time->start = now;
		time->last = now;
	}
	diff = now - time->start;
	diff_dt = now - time->last;
	time->now = (f64)diff / (f64)time->freq;
	time->dt = (f64)diff_dt / (f64)time->freq;
	time->last = now;
}
