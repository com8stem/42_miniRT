/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 06:30:07 by yutakagi          #+#    #+#             */
/*   Updated: 2024/09/10 16:00:44 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_3d_vec	local_to_global(t_3d_vec local_point, t_camera camera)
{
	t_3d_vec	global_point;
	t_3d_vec	forward;
	t_3d_vec	up;
	t_3d_vec	right;

	forward = vec_normalize(camera.orient);
	up.x = 0;
	up.y = 1;
	up.z = 0;
	right = vec_normalize(cross_product(forward, up));
	up = vec_normalize(cross_product(right, forward));
	global_point.x = right.x * local_point.x + up.x * local_point.y + forward.x
		* local_point.z + camera.initial_point.x;
	global_point.y = right.y * local_point.x + up.y * local_point.y + forward.y
		* local_point.z + camera.initial_point.y;
	global_point.z = right.z * local_point.x + up.z * local_point.y + forward.z
		* local_point.z + camera.initial_point.z;
	return (global_point);
}

t_3d_vec	ray_from_camera(int x, int y, t_camera camera)
{
	t_3d_vec	ray;
	t_3d_vec	screen_point_local;
	t_3d_vec	screen_point_global;

	screen_point_local = convert_screen_points(WIDTH - x - 1, HEIGHT - y - 1,
			camera.fov);
	screen_point_global = local_to_global(screen_point_local, camera);
	ray = generate_ray(screen_point_global, camera.initial_point);
	ray = vec_normalize(ray);
	return (ray);
}

static void	_init_status(t_detect_status *status)
{
	status->is_front = false;
	status->t_sphere = 0;
	status->t_plain = 0;
	status->t_cylinder = 0;
	status->min_distance = INFINITY;
}

int	set_color_map(t_rt_info *game)
{
	t_detect_status	status;

	_init_status(&status);
	status.y = 0;
	while (status.y < HEIGHT)
	{
		status.x = 0;
		while (status.x < WIDTH)
		{
			game->color_map[status.y][status.x] = BACKGROUND_COLOR;
			status.ray = ray_from_camera(status.x, status.y, game->camera);
			status.min_distance = INFINITY;
			detect_sphere_on_ray(game, &status);
			detect_plain_on_ray(game, &status);
			detect_cylinder_on_ray(game, &status);
			status.x += 1;
		}
		status.y += 1;
	}
	return (0);
}
