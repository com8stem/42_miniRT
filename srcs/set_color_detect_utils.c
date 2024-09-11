/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color_detect_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutakagi <yutakagi@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 07:11:29 by yutakagi          #+#    #+#             */
/*   Updated: 2024/09/11 17:52:17 by yutakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static bool	_detect_sp(t_rt_info *game, t_detect_status *st, int i)
{
	return (cross_detection_ray_and_sphere(st->ray, game->camera.initial_point,
			&game->sphere[i], st) && st->t_sphere > 0 && st->is_front);
}

void	detect_sphere_on_ray(t_rt_info *game, t_detect_status *st)
{
	int	i;

	i = -1;
	while (++i < game->sp_num)
	{
		st->t_sphere = 0;
		st->is_front = false;
		if (_detect_sp(game, st, i))
		{
			st->hit_point = vec_add(game->camera.initial_point,
					vec_scalar_mult(st->ray, st->t_sphere));
			st->distance = norm(vec_sub(game->camera.initial_point,
						st->hit_point));
			if (st->distance < st->min_distance)
			{
				st->min_distance = st->distance;
				st->shadow_ray = generate_ray(st->hit_point,
						game->light.initial_point);
				double light_distance = norm(vec_sub(st->hit_point,
						game->light.initial_point));
				if (!is_in_shadow(st->shadow_ray, st->hit_point, game, light_distance))
					set_color(game, st, 's', i);
				else
					set_color_shadow(game, st, 's', i);
			}
		}
	}
}

void	detect_plain_on_ray(t_rt_info *gm, t_detect_status *st)
{
	int	i;

	i = 0;
	while (i < gm->pl_num)
	{
		if (cross_detection_ray_and_plain(st->ray, gm->camera.initial_point,
				&gm->plain[i], &st->t_plain) && st->t_plain > 0)
		{
			st->hit_point = vec_add(gm->camera.initial_point,
					vec_scalar_mult(st->ray, st->t_plain));
			st->distance = norm(vec_sub(gm->camera.initial_point,
						st->hit_point));
			if (st->distance < st->min_distance)
			{
				st->min_distance = st->distance;
				st->shadow_ray = generate_ray(st->hit_point,
						gm->light.initial_point);
				double light_distance = norm(vec_sub(st->hit_point,
						gm->light.initial_point));
				if (!is_in_shadow(st->shadow_ray, st->hit_point, gm, light_distance))
					set_color(gm, st, 'p', i);
				else
					set_color_shadow(gm, st, 'p', i);
			}
		}
		i++;
	}
}

static bool	_cross_detect_cy(t_rt_info *game, t_detect_status *st, int i)
{
	return (cross_detection_ray_and_cylinder(st->ray,
			game->camera.initial_point, &game->cylinder[i], &st->t_cylinder)
		&& st->t_cylinder > 0);
}

void	detect_cylinder_on_ray(t_rt_info *game, t_detect_status *st)
{
	int	i;

	i = 0;
	while (i < game->cy_num)
	{
		if (_cross_detect_cy(game, st, i))
		{
			st->hit_point = vec_add(game->camera.initial_point,
					vec_scalar_mult(st->ray, st->t_cylinder));
			st->distance = norm(vec_sub(game->camera.initial_point,
						st->hit_point));
			if (st->distance < st->min_distance)
			{
				st->min_distance = st->distance;
				st->shadow_ray = generate_ray(st->hit_point,
						game->light.initial_point);
				double light_distance = norm(vec_sub(st->hit_point,
						game->light.initial_point));
				if (!is_in_shadow(st->shadow_ray, st->hit_point, game, light_distance))
					set_color(game, st, 'c', i);
				else
					set_color_shadow(game, st, 'c', i);
			}
		}
		i++;
	}
}
