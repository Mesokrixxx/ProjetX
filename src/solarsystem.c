#include "solarsystem.h"
#include "check.h"

solarsystem_t	solarsystem_init(void)
{
	solarsystem_t	solarsys = solarsystem_null;

	return solarsys;
}

void			solarsystem_update(solarsystem_t *solarsys)
{
	checkarg(solarsys);
}

void			solarsystem_tick(solarsystem_t *solarsys)
{
	checkarg(solarsys);
}

void			solarsystem_render(solarsystem_t *solarsys)
{
	checkarg(solarsys);
}

void			solarsystem_end(solarsystem_t *solarsys)
{
	checkarg(solarsys);
	*solarsys = solarsystem_null;
}
