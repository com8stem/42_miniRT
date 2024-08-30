#include "minirt.h"

int	check_line(char *line, t_rt_info *game)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens)
		return (0);
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
	return (0);
}

int	check_fileformat(char *filename, t_rt_info *game)
{
	int		fd;
	char	*line;
	char	*tmp;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		show_format_error('d');
	line = get_next_line(fd);
	while(line)
	{
		tmp = line;
		if (line)
			check_line(line, game);
		line = get_next_line(fd);
		free(tmp);
	}
	free(line);
	if (game->num_ambient != 1 || game->num_camera != 1
		|| game->num_light != 1)
		show_format_error('u');
	close(fd);
	return (0);
}
