#include "rand.h"
#include "types.h"
#include "log.h"
#include <stdlib.h>
#include <time.h>

static inline void	setseed(void);

int	randint(int limit)
{
	u64 max = (u64)RAND_MAX + 1;
	u64 limitull;

	if (limit <= 0)
	{
		error("called %s() with a wrong limit: %d", 
			__func__, limit);
		return (0);
	}
	setseed();
	limitull = limit;
	if (limitull <= max)
	{
		u64 bucket = (max / limitull) * limitull;
		u64 ret;

		do {
			ret = (u64)rand();
		}	while (ret >= bucket);
		return ((int)(ret % limitull));
	}
	for (;;)
	{
		u64 x = 0;
		u64 span = 1;

		do {
			x = x * max + (u64)rand();
			span *= max;
		} while (span < limitull);

		u64	end = (span / limitull) * limitull;

		if (x < end)
			return ((int)(x % limitull));
	}
}

static inline void	setseed(void)
{
	static bool	seedset;

	if (!seedset)
	{
		srand(time(NULL));
		seedset = true;
	}
}
