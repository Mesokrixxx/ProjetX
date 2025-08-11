#ifndef SDLTIME_H
# define SDLTIME_H

# include "types.h"

typedef struct sdltime_s {
	f64	now, dt; // In seconds
	u64 freq, start, last;
}	sdltime_t;

# define sdltime_null ((sdltime_t){0})

sdltime_t	time_init(void);
void		time_update(sdltime_t *time);

#endif
