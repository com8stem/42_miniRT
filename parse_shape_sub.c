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

void parse_cy(char **split, t_rt_info *game, int *cy_count)
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

void parse_pl(char **split, t_rt_info *game, int *pl_count)
{
	char	**tmp;

	tmp = ft_split(split[1], ',');
	if (count_token(tmp) != 3)
		config_error("Plain point format is wrong");
	game->plain[*pl_count].point.x = ft_atob(tmp[0]);
	game->plain[*pl_count].point.y = ft_atob(tmp[1]);
	game->plain[*pl_count].point.z = ft_atob(tmp[2]);
	free_split(tmp);
	tmp = ft_split(split[2], ',');
	if (count_token(tmp) != 3)
		config_error("Plain normal format is wrong");
	game->plain[*pl_count].normal.x = ft_atob(tmp[0]);
	game->plain[*pl_count].normal.y = ft_atob(tmp[1]);
	game->plain[*pl_count].normal.z = ft_atob(tmp[2]);
	free_split(tmp);
	tmp = ft_split(split[3], ',');
	_is_valid_pl(game, tmp, *pl_count);
	game->plain[*pl_count].color.r = ft_atoi(tmp[0]);
	game->plain[*pl_count].color.g = ft_atoi(tmp[1]);
	game->plain[*pl_count].color.b = ft_atoi(tmp[2]);
	free_split(tmp);
	check_color_range(game->plain[*pl_count].color.r,
		game->plain[*pl_count].color.g, game->plain[*pl_count].color.b);
	*pl_count += 1;
}