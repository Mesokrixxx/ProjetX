#ifndef PX_IO_H
# define PX_IO_H

# include "types.h"

# define STDIN	0
# define STDOUT	1
# define STDERR	2

ssize_t	px_write(int fd, const void *buf, size_t count);

#endif
