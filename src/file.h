#ifndef FILE_H
# define FILE_H

# include "types.h"

bool	file_exists(const char *path);
char	*file_read(const char *path);

#endif
