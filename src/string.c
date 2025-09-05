#include "string.h"

#include <stdlib.h>

u64	px_strlen(const char *s)
{
	u64	ret;

	if (!s)
		return 0;
	for (ret = 0; s[ret]; ret++)
		;
	return ret;
}

char	*px_strdup(const char *s)
{
	char	*ret;
	u64		retlen;

	if (!s)
		return NULL;
	retlen = px_strlen(s);
	if (!retlen)
		return NULL;
	ret = malloc(sizeof(char) * (retlen + 1));
	if (!ret)
		return NULL;
	for (u64 i = 0; i < retlen; i++)
		ret[i] = s[i];
	ret[retlen] = 0;
	return ret;
}

char	*px_strndup(const char *s, u64 n)
{
	char	*ret;

	if (!s || !n)
		return NULL;
	ret = malloc(sizeof(char) * (n + 1));
	if (!ret)
		return NULL;
	for (u64 i = 0; i < n; i++)
		ret[i] = s[i];
	ret[n] = 0;
	return ret;
}

bool	px_strcmp(const char *s1, const char *s2)
{
	u64	i;

	if (!s1 || !s2)
		return false;
	for (i = 0; s1[i] && s2[i] && s1[i] == s2[i]; i++)
		;
	return (s1[i] - s2[i]) == 0;
}
