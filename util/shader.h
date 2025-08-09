#ifndef SHADER_H
# define SHADER_H

# include "types.h"

typedef struct shader_s {
	u32	id;
}	shader_t;

# define shader_null ((shader_t){0})

/**
* vsp and fsp are nullable, used to compile shader at creation time
**/
shader_t	shader_create(const char *vsp, const char *fsp);
/**
* vsp: vertex source path.
* fsp: fragment source path.
**/
void		shader_compile(shader_t *shader, const char *vsp, const char *fsp);
void		shader_destroy(shader_t *shader);
void		shader_bind(shader_t *shader);
bool		shader_valid(shader_t *shader);

#endif
