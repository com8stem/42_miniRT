#include "minirt.h"

char **x_ft_split(const char *str, char c)
{
	char **result;
	result = ft_split(str, c);
	if (result == NULL)
		config_error("ft_split failed");
	return (result);
}

char *x_ft_strjoin(char const *s1, char const *s2)
{
	char *result;
	result = ft_strjoin(s1, s2);
	if (result == NULL)
		config_error("ft_strjoin failed");
	return (result);
}

char *x_ft_substr(const char *s, unsigned int start, size_t len)
{
	char *result;
	result = ft_substr(s, start, len);
	if (result == NULL)
		config_error("ft_substr failed");
	return (result);
}

void *x_ft_calloc(size_t count, size_t size)
{
	void *result;
	result = ft_calloc(count, size);
	if (result == NULL)
		config_error("calloc failed");
	return (result);
}

void *x_malloc(size_t size)
{
	void *result;
	result = malloc(size);
	if (result == NULL)
		config_error("malloc failed");
	return (result);
}
