/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_screen_points.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutakagi <yutakagi@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 06:29:43 by yutakagi          #+#    #+#             */
/*   Updated: 2024/09/02 06:29:48 by yutakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_3d_vec convert_screen_points(int x, int y, double fov)
{
	t_3d_vec	converted_point;
	double		aspect_ratio;
	double		scale;

	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	scale = tan((fov * 0.5 * 3.14159265358979323846) / 180.0);
	converted_point.x = (2.0 * (double)x / (double)WIDTH - 1.0) *
		aspect_ratio * scale;
	converted_point.y = (1.0 - 2.0 * (double)y / (double)HEIGHT) * scale;
	converted_point.z = -1.0;

	return (converted_point);
}
