/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color_detect_utils_sub.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:00:25 by kishizu           #+#    #+#             */
/*   Updated: 2024/09/14 15:03:17 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	calc_dist_hit_point(t_rt_info *game, t_detect_status *st, double t)
{
	st->hit_point = vec_add(game->camera.initial_point,
			vec_scalar_mult(st->ray, t));
	st->distance = norm(vec_sub(game->camera.initial_point, st->hit_point));
}
