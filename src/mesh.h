#ifndef MESH_H
# define MESH_H

# include "glbuffer.h"
# include "types.h"

# define _MESHSBUFFERCOUNT 4

typedef enum meshtype_e : u8 {
	MESH_INVALID,
	MESH_INSTANCED_ELEMENT,
	_MESHTYPE_COUNT
}	meshtype_t;

typedef struct mesh_s {
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
	meshtype_t			type;
}	mesh_t;

# define mesh_null ((mesh_t){0})

typedef struct meshattributes_s {
	u64		offset;
	u32		gltype;
	u8		size;
	bool	normalized;
}	meshattributes_t;

typedef struct meshsetup_s {
	struct {
		void				*data;
		u64					unitsize;
		meshattributes_t	*attributes;
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
		meshattributes_t	*attributes;
		u32					attributes_count;
		u32					capacity;
		u32					usage;
	}	instances;
}	meshsetup_t;

mesh_t	mesh_create(meshtype_t type);
void	mesh_setup(mesh_t *mesh, meshsetup_t desc);
void	mesh_draw(mesh_t *mesh, u64 offset, u32 glmode);
void	mesh_append(mesh_t *mesh, u32 icount, void *instances);
void	mesh_destroy(mesh_t *mesh);
bool	mesh_valid(mesh_t *mesh);
void	mesh_clear(mesh_t *mesh);

#endif