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

void show_format_error(char c)
{
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


void free_tokens(char **token)
{
	int i;

	i = 0;
	while (token[i])
	{
		free(token[i]);
		i++;
	}
	free(token);
}

void check()
{
	printf("here\n");
	return ;
}

void check_a(char **line)
{
	int i;

	i = 0;
	while(line[i]!=NULL)
		i++;
	if (i != 3)
		show_format_error('u');
}

int check_line(char *line)
{
	char **tokens;

	tokens = ft_split(line, ' ');
	if (!tokens)
	{
		printf("check\n");
		return 0;
	}
	if ((ft_strncmp(tokens[0], "R", 2) == 0) || (ft_strncmp(tokens[0], "A", 2) == 0)
		|| (ft_strncmp(tokens[0], "C", 2) == 0) || (ft_strncmp(tokens[0], "L", 2) == 0)
		|| (ft_strncmp(tokens[0], "cy", 3) == 0) || (ft_strncmp(tokens[0], "pl", 3) == 0)
		|| (ft_strncmp(tokens[0], "sp", 3) == 0))
		;
	else
		show_format_error('u');
	free_tokens(tokens);
	return 0;
}

int check_fileformat(char *filename)
{
	int fd;
	char *line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		show_format_error('d');
	line = get_next_line(fd);
	while(line)
	{
		char *tmp;
		tmp = line;
		if (line)
			check_line(line);
		line = get_next_line(fd);
		free(tmp);
	}
	// check_line(line);
	free(line);

	close(fd);
	return (0);	
}
