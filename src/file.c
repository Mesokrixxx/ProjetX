#include "file.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "types.h"

bool	file_exists(const char *path)
{
	if (!access(path, F_OK))
		return true;
	return false;
}

char	*file_read(const char *path)
{
	FILE	*f;
	char	*ret;
	u64		fsize;
	
	if (!path)
		return NULL;
	f = fopen(path, "rb");
	if (!f)
	{
		fprintf(stderr, "failed to open %s\n", path);
		return NULL;
	}
	fseek(f, 0, SEEK_END);
	fsize = ftell(f);
	fseek(f, 0, SEEK_SET);
	ret = malloc(sizeof(char) * (fsize + 1));
	if (!ret)
		goto end;
	if (fread(ret, sizeof(char), fsize, f) != fsize)
	{
		free(ret);
		ret = NULL;
		goto end;
	}
	ret[fsize] = 0;
end:
	fclose(f);
	return ret;
}
