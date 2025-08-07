#ifndef LOG_H
# define LOG_H

# include <stdio.h>

# define _PRINTLOG(io, logtype, fmt, ...)					\
	do {													\
		fprintf(io, "[%s][%s::%d]\n>>> " fmt "\n",				\
			logtype, __FILE__, __LINE__, ##__VA_ARGS__);	\
	} while (0)

# define log(fmt, ...) _PRINTLOG(stdout, "LOG", fmt, ##__VA_ARGS__)
# define warn(fmt, ...) _PRINTLOG(stderr, "WARN", fmt, ##__VA_ARGS__)
# define error(fmt, ...) _PRINTLOG(stderr, "ERROR", fmt, ##__VA_ARGS__)

/**
* check if an argument is null, if it is: call an error log and a return statement
**/
# define nullarg(arg) 											\
	do {														\
		if (!(arg)) {											\
			error("argument '%s' is null (from function '%s')",	\
				#arg, __func__);								\
			return ;											\
		}														\
	} while (0)

#endif
