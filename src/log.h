#ifndef LOG_H
# define LOG_H

# include <stdio.h>

# define CNRM	"\x1B[0m"
# define CRED	"\x1B[31m"
# define CYEL	"\x1B[33m"
# define CBLU	"\x1B[34m"

# define _PRINTLOG(io, logtype, fmt, ...)					\
	do {													\
		fprintf(io, "[%s][%s::%d]\n>>> " fmt "\n",				\
			logtype, __FILE__, __LINE__, ##__VA_ARGS__);	\
	} while (0)

# define log(fmt, ...) _PRINTLOG(stdout, CBLU "LOG" CNRM, fmt, ##__VA_ARGS__)
# define warn(fmt, ...) _PRINTLOG(stderr, CYEL "WARN" CNRM, fmt, ##__VA_ARGS__)
# define error(fmt, ...) _PRINTLOG(stderr, CRED "ERROR" CNRM, fmt, ##__VA_ARGS__)

#endif
