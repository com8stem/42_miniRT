/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 06:30:24 by yutakagi          #+#    #+#             */
/*   Updated: 2024/09/10 16:00:34 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	print_rtinfo_subsub(t_rt_info *game)
{
	int	i;

	i = 0;
	while (i < game->sp_num)
	{
		printf("sphere.center_point: %f, %f, %f\n",
			game->sphere[i].center_point.x, game->sphere[i].center_point.y,
			game->sphere[i].center_point.z);
		printf("sphere.diameter: %f\n", game->sphere[i].diameter);
		printf("sphere.color: %d, %d, %d\n", game->sphere[i].color.r,
			game->sphere[i].color.g, game->sphere[i].color.b);
		i++;
	}
	i = 0;
	while (i < game->pl_num)
	{
		printf("plain.point: %f, %f, %f\n", game->plain[i].point.x,
			game->plain[i].point.y, game->plain[i].point.z);
		printf("plain.normal: %f, %f, %f\n", game->plain[i].normal.x,
			game->plain[i].normal.y, game->plain[i].normal.z);
		printf("plain.color: %d, %d, %d\n", game->plain[i].color.r,
			game->plain[i].color.g, game->plain[i].color.b);
		i++;
	}
	return ;
}

static void	print_rtinfo_sub(t_rt_info *game)
{
	printf("ambient_light.ratio: %f\n", game->ambient_light.ratio);
	printf("ambient_light.color: %d, %d, %d\n", game->ambient_light.color.r,
		game->ambient_light.color.g, game->ambient_light.color.b);
	printf("camera.initial_point: %f, %f, %f\n", game->camera.initial_point.x,
		game->camera.initial_point.y, game->camera.initial_point.z);
	printf("camera.orient: %f, %f, %f\n", game->camera.orient.x,
		game->camera.orient.y, game->camera.orient.z);
	printf("camera.fov: %f\n", game->camera.fov);
	printf("light.initial_point: %f, %f, %f\n", game->light.initial_point.x,
		game->light.initial_point.y, game->light.initial_point.z);
	printf("light.brightness: %f\n", game->light.brightness);
	printf("light.color: %d, %d, %d\n", game->light.color.r,
		game->light.color.g, game->light.color.b);
	return ;
}

void	print_rtinfo(t_rt_info *game)
{
	int i;

	print_rtinfo_sub(game);
	print_rtinfo_subsub(game);
	i = 0;
	while (i < game->cy_num)
	{
		printf("cylinder.center_point: %f, %f, %f\n",
			game->cylinder[i].center_point.x, game->cylinder[i].center_point.y,
			game->cylinder[i].center_point.z);
		printf("orient: %f, %f, %f\n", game->cylinder[i].orient.x,
			game->cylinder[i].orient.y, game->cylinder[i].orient.z);
		printf("diameter: %f\n", game->cylinder[i].diameter);
		printf("height: %f\n", game->cylinder[i].height);
		printf("color: %d, %d, %d\n", game->cylinder[i].color.r,
			game->cylinder[i].color.g, game->cylinder[i].color.b);
		i++;
	}
	return ;
}