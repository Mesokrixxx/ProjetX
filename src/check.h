#ifndef CHECK_H
# define CHECK_H

# include "log.h"

# define _CHECK(val, ...)	\
	do {					\
		if (!(val)) {		\
			__VA_ARGS__		\
		}					\
	} while (0)

# define checkarg(arg)					\
	_CHECK(arg, 						\
		error("argument '%s' is null "	\
			"(when calling %s())",		\
			#arg, __func__);			\
		return ;						\
	)

# define checkargv(arg, v)				\
	_CHECK(arg,							\
		error("argument '%s' is null "	\
			"(when calling %s())",		\
			#arg, __func__);			\
		return (v);						\
	)

# define checkalloc(var, size, ...)							\
	_CHECK(var,												\
		error("failed to allocate %zu bytes "				\
			"(when allocating for '%s' in function '%s'",	\
			size, #var, __func__);							\
		__VA_ARGS__											\
		return ;											\
	)

# define checkallocv(var, size, v, ...)						\
	_CHECK(var,												\
		error("failed to allocate %zu bytes "				\
			"(when allocating for '%s' in function '%s'",	\
			size, #var, __func__);							\
		__VA_ARGS__											\
		return (v);											\
	)

#endif
