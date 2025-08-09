#ifndef VECTORS_H
# define VECTORS_H

# define v3		vec3_t
# define v3_of	vec3_of

typedef union vec3_u {
	struct {
		float x, y, z;
	};
	float _raw[3];
}	vec3_t;

static inline vec3_t	vec3_of(float x, float y, float z)
{
	return ((vec3_t){{ x, y, z }});
}

#endif