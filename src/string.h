#ifndef STRING_H
# define STRING_H

# include "types.h"

// Return the lenght of a string
u64		px_strlen(const char *s);
// Return an allocated copy of a string, returned pointer has to be freed
char	*px_strdup(const char *s);
// Return an allocated copy of n chararters of a string, returned pointer has to be freed
char	*px_strndup(const char *s, u64 n);
// Return a boolean regarding the equivalance of two strings
bool	px_strcmp(const char *s1, const char *s2);

#endif
