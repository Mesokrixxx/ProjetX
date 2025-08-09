#ifndef FILE_H
# define FILE_H

# include "types.h"

typedef struct file_s {
	char	*content;
	u64		size;
}	file_t;

# define file_null ((file_t){0})

/**
* argument path is nullable, can be use to load file at creation time
**/
file_t	file_create(const char *path);
/**
* You need to manually unload the file to prevent memory leaks
**/
void	file_load(file_t *file, const char *path);
void	file_unload(file_t *file);
bool	file_valid(file_t *file);

#endif