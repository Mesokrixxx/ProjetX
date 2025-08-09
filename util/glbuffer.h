#ifndef GLBUFFER_H
# define GLBUFFER_H

# include "types.h"

typedef enum glbuffertype_e : u8 {
	GLBUFFER_INVALID,
	GLBUFFER_ARRAY,
	GLBUFFER_ELEMENT,
	GLBUFFER_VERTEX_ARRAY,
	_GLBUFFERTYPE_COUNT,
}	glbuffertype_t;

typedef struct glbuffer_s {
	u64 			size;
	u32				id;
	glbuffertype_t	type;
}	glbuffer_t;

# define glbuffer_null ((glbuffer_t){0})

// Automatically bind created buffer
glbuffer_t	glbuffer_create(glbuffertype_t type);
void		glbuffer_bind(glbuffer_t *buffer);
void		glbuffer_data(glbuffer_t *buffer, u64 datasize, 
	void *data, u32 glusage);
void		glbuffer_subdata(glbuffer_t *buffer, u64 offset,
	u64 datasize, void *data);
void		glbuffer_destroy(glbuffer_t *buffer);
bool		glbuffer_valid(glbuffer_t *buffer);

#endif
