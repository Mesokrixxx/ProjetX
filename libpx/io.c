#include "io.h"
#include "sys.h"

ssize_t px_write(int fd, const void *buf, size_t count)
{
	ssize_t	ret;

	asm volatile (
		"syscall"
		: "=a"(ret)
		: "a"(SYSCALL_WRITE), "D"(fd), "S"(buf), "d"(count)
		: "rcx", "r11", "memory"
	);
	return ret;
}
