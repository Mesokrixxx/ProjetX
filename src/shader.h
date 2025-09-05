#ifndef SHADER_H
# define SHADER_H

# include "types.h"

typedef struct {
	char	*vsp, *fsp;
	u32		id;
}	shader_t;

void	shader_create(shader_t *s, const char *vsp, const char *fsp);
void	shader_bind(shader_t *s);
void	shader_reload(shader_t *s);
void	shader_destroy(shader_t *s);

#endif
