#include "minirt.h"

int check_argc(int argc)
{
	if (argc != 2)
	{
		printf("Error\n");
		printf("Error: Invalid number of arguments\n");
		exit(1);
	}
	return (0);
}

void show_format_error(char c)
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

void check_a(char **line)
{
	int i;

	i = 0;
	while(line[i]!=NULL)
		i++;
	if (i != 3)
		show_format_error('u');
}


int check_line(char *line, t_rt_info *game)
{
	char **tokens;

	tokens = ft_split(line, ' ');
	if (!tokens)
		return 0;
	if (ft_strncmp(tokens[0], "A", 2) == 0)
		game->num_ambient += 1;
	else if (ft_strncmp(tokens[0], "C", 2) == 0)
		game->num_camera += 1;
	else if (ft_strncmp(tokens[0], "L", 2) == 0)
		game->num_light += 1;
	else if (ft_strncmp(tokens[0], "sp", 3) == 0)
		game->sp_num += 1;
	else if (ft_strncmp(tokens[0], "cy", 3) == 0)
		game->cy_num += 1;
	else if (ft_strncmp(tokens[0], "pl", 3) == 0)
		game->pl_num += 1;
	else if (ft_strncmp(tokens[0], "sp", 3) == 0)
		game->sp_num += 1;
	else
		show_format_error('u');
	free_tokens(tokens);
	return 0;
}

int check_fileformat(char *filename, t_rt_info *game)
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
			check_line(line, game);
		line = get_next_line(fd);
		free(tmp);
	}
	free(line);
	if (game->num_ambient != 1 || game->num_camera != 1 || game->num_light != 1)
		show_format_error('u');

	close(fd);
	return (0);	
}
