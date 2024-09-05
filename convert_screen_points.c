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
	double		theta;

	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	theta = fov * 0.5 * 3.14159265358979323846 / 180.0;
	if (theta == 0)
		theta = 0.01;
	else if(theta > 1.5)
		theta = 1.5;
	scale = tan(theta);
	converted_point.x = (2.0 * (double)x / (double)WIDTH - 1.0) *
		aspect_ratio * scale;
	converted_point.y = (1.0 - 2.0 * (double)y / (double)HEIGHT) * scale;
	converted_point.z = -1.0;

	return (converted_point);
}
