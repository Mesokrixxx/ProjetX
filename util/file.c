#include "file.h"
#include "log.h"
#include "check.h"
#include <stdlib.h>

file_t	file_create(const char *path)
{
	file_t	f = file_null;

	if (path)
		file_load(&f, path);
	return (f);
}

void	file_load(file_t *file, const char *path)
{
	FILE	*stream;
	size_t	read_ret;

	checkarg(path);
	checkarg(file);
	stream = fopen(path, "rb");
	if (!stream)
	{
		error("failed to load %s", path);
		return ;
	}
	fseek(stream, 0, SEEK_END);
	file->size = ftell(stream);
	fseek(stream, 0, SEEK_SET);
	file->content = malloc(sizeof(char) * (file->size + 1));
	checkalloc(file->content, file->size + 1, 
		fclose(stream);
	);
	read_ret = fread(file->content, sizeof(char), file->size, stream);
	if (read_ret != file->size)
	{
		error("failed to read %zu bytes from %s, got %zu", 
			file->size, path, read_ret);
		free(file->content);
		fclose(stream);
		return ;
	}
	file->content[file->size] = '\0';
	fclose(stream);
}


void	file_unload(file_t *file)
{
	checkarg(file);
	if (file->content)
		free(file->content);
	else
		warn("called %s() when it wasn't necessary",
			__func__);
	*file = file_null;
}

bool	file_valid(file_t *file)
{
	checkargv(file, false);
	return (file->content && file->size);
}
