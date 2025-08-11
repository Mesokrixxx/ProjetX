#ifndef SHADER_H
# define SHADER_H

# include "types.h"

typedef struct glshader_s {
	u32	id;
}	glshader_t;

# define glshader_null ((glshader_t){0})

/**
* vsp and fsp are nullable, used to compile shader at creation time
**/
glshader_t	glshader_create(const char *vsp, const char *fsp);
/**
* vsp: vertex source path.
* fsp: fragment source path.
**/
void		glshader_compile(glshader_t *shader, const char *vsp, const char *fsp);
void		glshader_destroy(glshader_t *shader);
void		glshader_bind(glshader_t *shader);
bool		glshader_valid(glshader_t *shader);

#endif
