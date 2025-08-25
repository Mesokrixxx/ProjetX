#include "io.h"
#include "std.h"

void _start()
{
	px_write(STDOUT, "Hello, World!\n", 14);
	px_exit(EXIT_SUCCESS);
}
