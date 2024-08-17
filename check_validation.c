#include "minirt.h"

int check_argc(int argc)
{
	if (argc != 2)
	{
		printf("Error: Invalid number of arguments\n");
		exit(1);
	}
	return (0);
}

int check_filename(char *filename)
{
	int i;

	i = 0;
	while (filename[i])
		i++;
	if (filename[i - 1] != 't' || filename[i - 2] != 'r' || filename[i - 3] != '.')
	{
		printf("Error: Invalid file extension\n");
		exit(1);
	}
	return (0);
}

int check_fileformat(char *filename)
{
	int fd;
	char *line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: File does not exist\n");
		exit(1);
	}
	line = get_next_line(fd);
	if (ft_strncmp(line, "R ", 2) != 0)
	{
		printf("Error: Resolution not found\n");
		exit(1);
	}
	free(line);
	close(fd);
	return (0);	
}
