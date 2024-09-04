/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shape_sub.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutakagi <yutakagi@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 07:15:15 by yutakagi          #+#    #+#             */
/*   Updated: 2024/09/04 10:21:02 by yutakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_color_range(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		config_error("Color range should be between 0 and 255");
	return ;
}

static void	_is_valid_cy(t_rt_info *game, char **tmp, int cy_count, t_cylinder tmp_cy)
{
	if (count_token(tmp) != 3 ||(game->cylinder[cy_count].orient.x == 0
			&& game->cylinder[cy_count].orient.y == 0
			&& game->cylinder[cy_count].orient.z == 0)
			|| game->cylinder[cy_count].height <= 0
			|| game->cylinder[cy_count].diameter <= 0)
		config_error("Cylinder orinet, height and diameter can not be zero");
	check_color_range(tmp_cy.color.r, tmp_cy.color.g, tmp_cy.color.b);
	return ;
}

void	parse_cy(char **split, t_rt_info *game, int *cy_count)
{
	char	**tmp;

	tmp = ft_split(split[1], ',');
	if (count_token(tmp) != 3)
		config_error("Cylinder center point format is wrong");
	game->cylinder[*cy_count].center_point.x = ft_atob(tmp[0]);
	game->cylinder[*cy_count].center_point.y = ft_atob(tmp[1]);
	game->cylinder[*cy_count].center_point.z = ft_atob(tmp[2]);
	free_split(tmp);
	tmp = ft_split(split[2], ',');
	if (count_token(tmp) != 3)
		config_error("Cylinder orient format is wrong");
	game->cylinder[*cy_count].orient.x = ft_atob(tmp[0]);
	game->cylinder[*cy_count].orient.y = ft_atob(tmp[1]);
	game->cylinder[*cy_count].orient.z = ft_atob(tmp[2]);
	free_split(tmp);
	game->cylinder[*cy_count].diameter = ft_atob(split[3]);
	game->cylinder[*cy_count].height = ft_atob(split[4]);
	tmp = ft_split(split[5], ',');
	game->cylinder[*cy_count].color.r = ft_atoi(tmp[0]);
	game->cylinder[*cy_count].color.g = ft_atoi(tmp[1]);
	game->cylinder[*cy_count].color.b = ft_atoi(tmp[2]);
	free_split(tmp);
	_is_valid_cy(game, tmp, *cy_count, game->cylinder[*cy_count]);
	*cy_count += 1;
}

static void	_is_valid_pl(t_rt_info *game, char **tmp, int pl_count)
{
	if (count_token(tmp) != 3 ||
		(game->plain[pl_count].normal.x == 0
		&& game->plain[pl_count].normal.y == 0
		&& game->plain[pl_count].normal.z == 0))
		config_error("Plain color format is wrong");
	return ;
}

void	parse_pl(char **split, t_rt_info *game, int *pl)
{
	char	**tmp;

	tmp = ft_split(split[1], ',');
	if (count_token(tmp) != 3)
		config_error("Plain point format is wrong");
	game->plain[*pl].point.x = ft_atob(tmp[0]);
	game->plain[*pl].point.y = ft_atob(tmp[1]);
	game->plain[*pl].point.z = ft_atob(tmp[2]);
	free_split(tmp);
	tmp = ft_split(split[2], ',');
	if (count_token(tmp) != 3)
		config_error("Plain normal format is wrong");
	game->plain[*pl].normal.x = ft_atob(tmp[0]);
	game->plain[*pl].normal.y = ft_atob(tmp[1]);
	game->plain[*pl].normal.z = ft_atob(tmp[2]);
	free_split(tmp);
	tmp = ft_split(split[3], ',');
	_is_valid_pl(game, tmp, *pl);
	game->plain[*pl].color.r = ft_atoi(tmp[0]);
	game->plain[*pl].color.g = ft_atoi(tmp[1]);
	game->plain[*pl].color.b = ft_atoi(tmp[2]);
	free_split(tmp);
	check_color_range(game->plain[*pl].color.r,
		game->plain[*pl].color.g, game->plain[*pl].color.b);
	*pl += 1;
}
