#include "minirt.h"

int	check_argc(int argc)
{
	if (argc != 2)
	{
		printf("Error\n");
		printf("Error: Invalid number of arguments\n");
		exit(1);
	}
	return (0);
}

void	show_format_error(char c)
{
	printf("Error\n");
	if (c == 'n')
		printf("Error: File does not exist\n");
	else if(c == 'r')
		printf("Error: Resolution not found\n");
	if (c == 'f')
		printf("Error: Invalid file extension\n");
	if (c == 'd')
		printf("Error: File does not exist\n");
	if (c == 'u')
		printf("Error: unexpected configuration\n");
	exit(1);
}

int check_filename(char *filename)
{
	int i;

	i = 0;
	if (!filename || ft_strlen(filename) <= 3)
		show_format_error('f');
	while (filename[i])
		i++;
	if (filename[i - 1] != 't' || filename[i - 2] != 'r' || filename[i - 3] != '.')
		show_format_error('f');
	return (0);	
}

void	free_tokens(char **token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		free(token[i]);
		i++;
	}
	free(token);
}
