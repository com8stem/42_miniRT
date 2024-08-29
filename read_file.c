#include "minirt.h"

int	file_open(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: File does not exist\n");
		exit(1);
	}
	return (fd);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	count_token(char **line)
{
	int	i;

	i = 0;
	while(line[i]!=NULL)
		i++;
	return (i);
}

int	parse_rtfile(int fd, t_rt_info *game)
{
	char *line;
	char **split;
	int sp_count;
	int pl_count;
	int cy_count;

	sp_count = 0;
	pl_count = 0;
	cy_count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		split = ft_split(line, ' ');
		free(line);
		if (split == NULL)
			break;
		if (ft_strncmp(split[0], "A", 2) == 0)
			parse_a(split, game);
		else if (ft_strncmp(split[0], "C", 2) == 0)
			parse_c(split, game);
		else if (ft_strncmp(split[0], "L", 2) == 0)
			parse_l(split, game);
		else if (ft_strncmp(split[0], "sp", 3) == 0)
			parse_sp(split, game, &sp_count);
		else if (ft_strncmp(split[0], "pl", 3) == 0)
			parse_pl(split, game, &pl_count);
		else if (ft_strncmp(split[0], "cy", 3) == 0)
			parse_cy(split, game, &cy_count);
		free_split(split);
	}
	return (0);
}

int	read_rtfile(char *filename, t_rt_info *game)
{
	int	fd;

	fd = file_open(filename);
	parse_rtfile(fd, game);
	print_rtinfo(game);
	close(fd);
	return (0);
}
