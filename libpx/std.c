#include "std.h"
#include "sys.h"

void	px_exit(int errcode)
{
	asm volatile (
		"syscall"
		:
		: "a"(SYSCALL_EXIT), "D"(errcode)
		: "rcx", "r11", "memory"
	);
}
