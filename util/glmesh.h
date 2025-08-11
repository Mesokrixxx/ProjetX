#ifndef MESH_H
# define MESH_H

# include "glbuffer.h"
# include "types.h"

# define _MESHSBUFFERCOUNT 4

typedef enum glmeshtype_e : u8 {
	GLMESH_INVALID,
	GLMESH_INSTANCED_ELEMENT,
	_GLMESHTYPE_COUNT
}	glmeshtype_t;

typedef struct glmesh_s {
	union {
		struct {
			glbuffer_t	vao;
			glbuffer_t	vbo;
			glbuffer_t	ebo;
			glbuffer_t	ibo;
		};
		glbuffer_t		buffers[_MESHSBUFFERCOUNT];
	};
	u64					isize;
	u32					ecount, gletype, icount;
	u32					icap;
	glmeshtype_t		type;
}	glmesh_t;

# define glmesh_null ((glmesh_t){0})

typedef struct glmeshattributes_s {
	u64		offset;
	u32		gltype;
	u8		size;
	bool	normalized;
}	glmeshattributes_t;

typedef struct glmeshsetup_s {
	struct {
		void				*data;
		u64					unitsize;
		glmeshattributes_t	*attributes;
		u32					count;
		u32					attributes_count;
		u32					usage;
	}	vertices;
	struct {
		void	*data;
		u64		totlsize;
		u32		gltype;
		u32		count;
		u32		usage;
	}	elements;
	struct {
		u64					unitsize;
		glmeshattributes_t	*attributes;
		u32					attributes_count;
		u32					capacity;
		u32					usage;
	}	instances;
}	glmeshsetup_t;

glmesh_t	glmesh_create(glmeshtype_t type);
void		glmesh_setup(glmesh_t *mesh, glmeshsetup_t desc);
void		glmesh_draw(glmesh_t *mesh, u64 offset, u32 glmode);
void		glmesh_append(glmesh_t *mesh, u32 icount, void *instances);
void		glmesh_destroy(glmesh_t *mesh);
bool		glmesh_valid(glmesh_t *mesh);
void		glmesh_clear(glmesh_t *mesh);

#endif
