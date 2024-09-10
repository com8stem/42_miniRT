/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 06:30:46 by yutakagi          #+#    #+#             */
/*   Updated: 2024/09/10 18:46:10 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	config_error(char *message)
{
	printf("Error\n");
	printf("%s\n", message);
	exit(1);
}

void	parse_sp(char **split, t_rt_info *game, int *sp_count)
{
	char	**tmp;

	tmp = x_ft_split(split[1], ',');
	if (count_token(tmp) != 3)
		config_error("Sphere center point format is wrong");
	game->sphere[*sp_count].center_point.x = ft_atob(tmp[0]);
	game->sphere[*sp_count].center_point.y = ft_atob(tmp[1]);
	game->sphere[*sp_count].center_point.z = ft_atob(tmp[2]);
	free_split(tmp);
	game->sphere[*sp_count].diameter = ft_atob(split[2]);
	tmp = x_ft_split(split[3], ',');
	if (count_token(tmp) != 3 || game->sphere[*sp_count].diameter <= 0)
		config_error("Sphere diameter must be larger than zero");
	game->sphere[*sp_count].color.r = ft_atoi(tmp[0]);
	game->sphere[*sp_count].color.g = ft_atoi(tmp[1]);
	game->sphere[*sp_count].color.b = ft_atoi(tmp[2]);
	free_split(tmp);
	check_color_range(game->sphere[*sp_count].color.r,
		game->sphere[*sp_count].color.g, game->sphere[*sp_count].color.b);
	*sp_count += 1;
}

void	parse_l(char **split, t_rt_info *game)
{
	char	**tmp;

	tmp = x_ft_split(split[1], ',');
	if (count_token(tmp) != 3)
		config_error("Light initial point format is wrong");
	game->light.initial_point.x = ft_atob(tmp[0]);
	game->light.initial_point.y = ft_atob(tmp[1]);
	game->light.initial_point.z = ft_atob(tmp[2]);
	free_split(tmp);
	game->light.brightness = ft_atob(split[2]);
	tmp = x_ft_split(split[3], ',');
	if (count_token(tmp) != 3)
		config_error("Light color format is wrong");
	game->light.color.r = ft_atoi(tmp[0]);
	game->light.color.g = ft_atoi(tmp[1]);
	game->light.color.b = ft_atoi(tmp[2]);
	check_color_range(game->light.color.r, game->light.color.g,
		game->light.color.b);
	free_split(tmp);
	if (game->light.brightness < 0 || game->light.brightness > 1)
		config_error("Light brightness should be between 0 and 1");
}

void	parse_c(char **split, t_rt_info *game)
{
	char	**tmp;

	tmp = x_ft_split(split[1], ',');
	if (count_token(tmp) != 3)
		config_error("Camera initial point format is wrong");
	game->camera.initial_point.x = ft_atob(tmp[0]);
	game->camera.initial_point.y = ft_atob(tmp[1]);
	game->camera.initial_point.z = ft_atob(tmp[2]);
	free_split(tmp);
	tmp = x_ft_split(split[2], ',');
	if (count_token(tmp) != 3)
		config_error("Camera orient format is wrong");
	game->camera.orient.x = ft_atob(tmp[0]);
	game->camera.orient.y = ft_atob(tmp[1]);
	game->camera.orient.z = ft_atob(tmp[2]);
	free_split(tmp);
	if (game->camera.orient.x == 0 && game->camera.orient.y == 0
		&& game->camera.orient.z == 0)
		config_error("Camera orient is wrong");
	game->camera.fov = ft_atoi(split[3]);
	if (game->camera.fov <= 0 || game->camera.fov >= 180)
		config_error("Camera fov should be between 0 and 180");
	if (game->camera.orient.x < 1e-6 && game->camera.orient.z < 1e-6)
		game->camera.orient.x += 1e-4;
}

void	parse_a(char **split, t_rt_info *game)
{
	char	**tmp;

	game->ambient_light.ratio = ft_atob(split[1]);
	tmp = x_ft_split(split[2], ',');
	if (count_token(tmp) != 3)
		config_error("Ambient light color format is wrong");
	game->ambient_light.color.r = ft_atoi(tmp[0]);
	game->ambient_light.color.g = ft_atoi(tmp[1]);
	game->ambient_light.color.b = ft_atoi(tmp[2]);
	if (game->ambient_light.ratio < 0 || game->ambient_light.ratio > 1)
		config_error("Ambient light ratio should be between 0 and 1");
	check_color_range(game->ambient_light.color.r, game->ambient_light.color.g,
		game->ambient_light.color.b);
	free_split(tmp);
}
