/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutakagi <yutakagi@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 07:08:29 by yutakagi          #+#    #+#             */
/*   Updated: 2024/09/13 07:32:58 by yutakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static double calc_dis(t_3d_vec hit_point, t_3d_vec shadow_ray, double t)
{
	t_3d_vec cross_point = vec_add(hit_point, vec_scalar_mult(shadow_ray, t));
	return (norm(vec_sub(cross_point, hit_point)));
}

static bool	_shadow_sphere(t_3d_vec shadow_ray, t_3d_vec hit_point,
		t_rt_info *game, t_detect_status *st)
{
	int			j;
	t_3d_vec	hit_point_offset;
	double		light_distance;

	j = 0;
	while (j < game->sp_num)
	{
		t_3d_vec normal = vec_sub(hit_point, game->sphere[j].center_point);
		hit_point_offset = calc_offset(hit_point, normal, game->camera.initial_point, 1e-4);
		light_distance = norm(vec_sub(hit_point, game->light.initial_point));
		if (cross_detection_ray_and_sphere(shadow_ray, hit_point_offset,
				&game->sphere[j], st) && st->t_sphere > EPSILON && st->is_front && calc_dis(hit_point, shadow_ray, st->t_sphere) < light_distance)
			return (true);
		j++;
	}
	return (false);
}

bool	is_in_shadow(t_3d_vec shadow_ray, t_3d_vec hit_point, t_rt_info *game, double light_distance)
{
	int				j;
	t_detect_status	st;
	double			t;

	st.is_front = false;
	st.t_sphere = 0;
	if (_shadow_sphere(shadow_ray, hit_point, game, &st))
		return (true);
	j = 0;
	while (j < game->pl_num)
	{
		if (cross_detection_ray_and_plain(shadow_ray, calc_offset(hit_point, game->plain[j].normal, game->camera.initial_point, 1e-4),
				&game->plain[j], &t) && t > EPSILON && calc_dis(hit_point, shadow_ray, t) < light_distance)
				return (true);
		j++;
	}
	j = 0;
	while (j < game->cy_num)
	{
		if (cross_detection_ray_and_cylinder(shadow_ray, hit_point,
				&game->cylinder[j], &t) && t > EPSILON && calc_dis(hit_point, shadow_ray, t) < light_distance)
			return (true);
		j++;
	}
	return (false);
}

void	set_color(t_rt_info *game, t_detect_status *st, char object_type, int i)
{
	int	color;

	color = BACKGROUND_COLOR;
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
				game->plain[i].color.g, game->plain[i].color.b,
				game->light.brightness);
		color = apply_ambient(game, color);
	}
	else if (object_type == 'c')
	{
		color = convert_rgb_to_hex(game->cylinder[i].color.r,
				game->cylinder[i].color.g, game->cylinder[i].color.b,
				game->light.brightness);
		color = apply_ambient(game, color);
	}
	game->color_map[st->y][st->x] = color;
}

void	set_color_shadow(t_rt_info *game, t_detect_status *st, char object_type,
		int i)
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
