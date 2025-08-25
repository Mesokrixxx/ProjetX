#define SYSCALL_WRITE	1
#define SYSCALL_EXIT	60

#define EXIT_SUCCESS	0
#define EXIT_FAILURE	1

typedef __SIZE_TYPE__		size_t;
typedef signed long			ssize_t;

void	px_exit(int errcode)
{
	asm volatile (
		"syscall"
		:
		: "a"(SYSCALL_EXIT), "D"(errcode)
		: "rcx", "r11", "memory"
	);
}

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

void _start()
{
	px_write(0, "Hello, World!\n", 14);
	px_exit(EXIT_SUCCESS);
}
