/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 06:30:16 by yutakagi          #+#    #+#             */
/*   Updated: 2024/09/10 17:54:01 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static void	init_count(t_shape_count *count)
{
	count->sp_count = 0;
	count->pl_count = 0;
	count->cy_count = 0;
}

static void	select_parse(char **split, t_rt_info *game, t_shape_count *count)
{
	if (ft_strncmp(split[0], "A", 2) == 0)
		parse_a(split, game);
	else if (ft_strncmp(split[0], "C", 2) == 0)
		parse_c(split, game);
	else if (ft_strncmp(split[0], "L", 2) == 0)
		parse_l(split, game);
	else if (ft_strncmp(split[0], "sp", 3) == 0)
		parse_sp(split, game, &count->sp_count);
	else if (ft_strncmp(split[0], "pl", 3) == 0)
		parse_pl(split, game, &count->pl_count);
	else if (ft_strncmp(split[0], "cy", 3) == 0)
		parse_cy(split, game, &count->cy_count);
}

int	parse_rtfile(int fd, t_rt_info *game)
{
	char			*line;
	char			**split;
	t_shape_count	count;

	init_count(&count);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		split = x_ft_split(line, ' ');
		free(line);
		if (split == NULL)
			break ;
		select_parse(split, game, &count);
		free_split(split);
	}
	return (0);
}

int	read_rtfile(char *filename, t_rt_info *game)
{
	int	fd;

	fd = file_open(filename);
	parse_rtfile(fd, game);
	close(fd);
	return (0);
}
