/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutakagi <yutakagi@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 07:08:29 by yutakagi          #+#    #+#             */
/*   Updated: 2024/09/10 08:37:09 by yutakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	_shadow_sphere(t_3d_vec shadow_ray, t_3d_vec hit_point, t_rt_info *game,
							t_detect_status *st)
{
	int			j;
	t_3d_vec	hit_point_offset;

	j = 0;
	while (j < game->sp_num)
	{
		hit_point_offset = vec_add(hit_point,
			vec_scalar_mult(vec_sub(hit_point,
			game->sphere[j].center_point), 1e-3));
		if (cross_detection_ray_and_sphere(shadow_ray, hit_point_offset,
			&game->sphere[j], st) && st->t_sphere >  EPSILON && st->is_front)
			return (true);
		j++;
	}
	return (false);
}

bool	is_in_shadow(t_3d_vec shadow_ray, t_3d_vec hit_point,
						t_rt_info *game)
{
	int		j;
	t_detect_status	st;
	double	t;

	st.min_distance = INFINITY;
	st.is_front = false;
	st.t_sphere = 0;
	if (_shadow_sphere(shadow_ray, hit_point, game, &st))
		return (true);
	j = 0;
	while (j < game->pl_num)
	{
		if (cross_detection_ray_and_plain(shadow_ray, hit_point, &game->
			plain[j], &t) && t > EPSILON)
			return (true);
		j++;
	}
	j = 0;
	while (j < game->cy_num)
	{
		if (cross_detection_ray_and_cylinder(shadow_ray, hit_point,
			&game->cylinder[j], &t)
			&& t > EPSILON)
			return (true);
		j++;
	}
	return (false);
}

void	set_color(t_rt_info *game, t_detect_status *st, char object_type, int i)
{
	int	color;

	if (object_type == 's')
	{
		color = convert_rgb_to_hex(game->sphere[i].color.r,
			game->sphere[i].color.g, game->sphere[i].color.b,
				game->light.brightness);
		color = apply_ambient(game, color);
	}
	else if (object_type == 'p')
	{
		color = convert_rgb_to_hex(game->plain[i].color.r,
		game->plain[i].color.g, game->plain[i].color.b, game->light.brightness);
		color = apply_ambient(game, color);
	}
	else if (object_type == 'c')
	{
		color = convert_rgb_to_hex(game->cylinder[i].color.r,
			game->cylinder[i].color.g, game->cylinder[i].color.b,
				game->light.brightness);
		color = apply_ambient(game, color);
	}
	else
		color = BACKGROUND_COLOR;
	game->color_map[st->y][st->x] = color;
}

void	set_color_shadow(t_rt_info *game, t_detect_status *st, char object_type, int i)
{
	int	color;

	if (object_type == 's')
		color = convert_rgb_to_hex_shadow(game->sphere[i].color.r,
			game->sphere[i].color.g, game->sphere[i].color.b,
			game->light.brightness);
	else if (object_type == 'p')
		color = convert_rgb_to_hex_shadow(game->plain[i].color.r,
			game->plain[i].color.g, game->plain[i].color.b,
			game->light.brightness);
	else if (object_type == 'c')
		color = convert_rgb_to_hex_shadow(game->cylinder[i].color.r,
			game->cylinder[i].color.g, game->cylinder[i].color.b,
				game->light.brightness);
	else
		color = BACKGROUND_COLOR;
	game->color_map[st->y][st->x] = color;
}

