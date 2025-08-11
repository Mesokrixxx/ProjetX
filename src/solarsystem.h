#ifndef SOLARSYSTEM_H
# define SOLARSYSTEM_H

# include "types.h"
# include "glmesh.h"

typedef enum celestialbodytype_e : u8 {
	CELESTIALBODY_INVALID,
	CELESTIALBODY_SOLID,
	CELESTIALBODY_GAZ,
	CELESTIALBODY_PLASMA,
	_CELESTIALBODYTYPE_COUNT,
}	celestialbodytype_t;

typedef struct celestialbody_s {
	float				radius;
	float				mass;
	celestialbodytype_t	type;
}	celestialbody_t;

typedef struct solarsystem_s {
	glmesh_t		cb_mesh;
	celestialbody_t	*bodies;
	u32				bodiescount;
}	solarsystem_t;

# define solarsystem_null ((solarsystem_t){0})

solarsystem_t	solarsystem_init(void);
void			solarsystem_update(solarsystem_t *solarsys);
void			solarsystem_tick(solarsystem_t *solarsys);
void			solarsystem_render(solarsystem_t *solarsys);
void			solarsystem_end(solarsystem_t *solarsys);

#endif