/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color_utils_sub.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:14:39 by kishizu           #+#    #+#             */
/*   Updated: 2024/09/14 15:15:35 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

bool	detect_plain_wrapped(t_3d_vec shadow_ray, t_3d_vec hit_point,
		t_rt_info *game, double light_distance)
{
	int		j;
	double	t;

	j = 0;
	while (j < game->pl_num)
	{
		if (cross_detection_ray_and_plain(shadow_ray, calc_offset(hit_point,
					game->plain[j].normal, game->camera.initial_point, 1e-4),
				&game->plain[j], &t) && t > EPSILON && calc_dis(hit_point,
				shadow_ray, t) < light_distance)
			return (true);
		j++;
	}
	return (false);
}
