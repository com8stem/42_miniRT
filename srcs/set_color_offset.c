/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color_offset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutakagi <yutakagi@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 07:21:30 by yutakagi          #+#    #+#             */
/*   Updated: 2024/09/13 07:22:51 by yutakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_3d_vec	calc_offset(t_3d_vec hit_point, t_3d_vec normal, t_3d_vec camera_position, double offset_value)
{
	t_3d_vec	offset_direction;
	t_3d_vec	offset_hit_point;

	if (dot_product(vec_sub(camera_position, hit_point), normal) > 0)
	{
		offset_direction = vec_scalar_mult(normal, offset_value);
	}
	else
	{
		offset_direction = vec_scalar_mult(normal, -offset_value);
	}
	offset_hit_point = vec_add(hit_point, offset_direction);

	return (offset_hit_point);
}
