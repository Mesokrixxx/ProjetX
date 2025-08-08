#ifndef CHECK_H
# define CHECK_H

# include "log.h"

# define checkarg(arg) 							\
	do {										\
		if (!(arg)) {							\
			error("argument '%s' is null "		\
				"(when calling function '%s')",	\
				#arg, __func__);				\
			return ;							\
		}										\
	} while (0)

# define checkalloc(var, size, ...)								\
	do {														\
		if (!(var)) {											\
			error("failed to allocate %zu bytes "				\
				"(when allocating for '%s' in function '%s'",	\
				size, #var, __func__);							\
			__VA_ARGS__											\
			return ;											\
		}														\
	} while (0)

#endif
