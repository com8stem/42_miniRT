#include "minirt.h"

bool	is_in_shadow(t_3d_vec shadow_ray, t_3d_vec hit_point, t_rt_info *game)
{
	double t;
	int j;
	bool is_front;

	j = 0;
	while (j < game->sp_num)
	{
		t_3d_vec hit_point_offset = vec_add(hit_point, vec_scalar_mult(vec_sub(hit_point,game->sphere[j].center_point), 1e-3));
		if (cross_detection_ray_and_sphere(shadow_ray, hit_point_offset, game->sphere[j].center_point, game->sphere[j].diameter / 2, &t, &is_front) && t >  EPSILON && is_front)
			return (true);
		j++;
	}
	j = 0;
	while (j < game->pl_num)
	{
		if (cross_detection_ray_and_plain(shadow_ray, hit_point, game->plain[j].normal, game->plain[j].point, &t) && t > EPSILON )
			return (true);
		j++;
	}
	j = 0;
	while (j < game->cy_num)
	{
		if (cross_detection_ray_and_cylinder(shadow_ray, hit_point, game->cylinder[j].orient, game->cylinder[j].center_point, game->cylinder[j].height, game->cylinder[j].diameter, &t) && t > EPSILON)
		{
			return (true);
		}
		j++;
	}
	return false;
}

void	set_color(t_rt_info *game, int x, int y, char object_type, int i)
{
	int	color;

	if (object_type == 's')
	{
		color = convert_rgb_to_hex(game->sphere[i].color.r,
			game->sphere[i].color.g, game->sphere[i].color.b, game->light.brightness);
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
			game->cylinder[i].color.g, game->cylinder[i].color.b, game->light.brightness);
		color = apply_ambient(game, color);
	}
	else
		color = BACKGROUND_COLOR;
	game->color_map[y][x] = color;
}

void	set_color_shadow(t_rt_info *game, int x, int y, char object_type, int i)
{
	int	color;

	if (object_type == 's')
		color = convert_rgb_to_hex_shadow(game->sphere[i].color.r,
			game->sphere[i].color.g, game->sphere[i].color.b, game->light.brightness);
	else if (object_type == 'p')
		color = convert_rgb_to_hex_shadow(game->plain[i].color.r,
			game->plain[i].color.g, game->plain[i].color.b, game->light.brightness);
	else if (object_type == 'c')
		color = convert_rgb_to_hex_shadow(game->cylinder[i].color.r,
			game->cylinder[i].color.g, game->cylinder[i].color.b, game->light.brightness);
	else
		color = BACKGROUND_COLOR;
	game->color_map[y][x] = color;
}


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
	global_point.x = right.x * local_point.x + up.x * local_point.y
		+ forward.x * local_point.z + camera.initial_point.x;
	global_point.y = right.y * local_point.x + up.y * local_point.y
		+ forward.y * local_point.z + camera.initial_point.y;
	global_point.z = right.z * local_point.x + up.z * local_point.y
		+ forward.z * local_point.z + camera.initial_point.z;
	return (global_point);
}

int set_color_map(t_rt_info *game)
{
	int x, y;
	t_3d_vec ray;
	double min_distance, distance;
	double t_sphere, t_plain, t_cylinder;
	t_3d_vec hit_point, shadow_ray;
	int i;
	bool is_front;

	for (y = 0; y < HEIGHT; y++)
	{
		for (x = 0; x < WIDTH; x++)
		{
			game->color_map[y][x] = BACKGROUND_COLOR;
			t_3d_vec screen_point_local = convert_screen_points(WIDTH - x - 1, HEIGHT - y - 1, game->camera.fov);
			t_3d_vec screen_point_global = local_to_global(screen_point_local, game->camera);
			ray = generate_ray(screen_point_global, game->camera.initial_point);
			ray = vec_normalize(ray);
			i = 0;
			min_distance = INFINITY;
			while (i < game->sp_num)
			{
				t_sphere = 0;
				is_front = false;
				if (cross_detection_ray_and_sphere(ray, game->camera.initial_point, game->sphere[i].center_point, game->sphere[i].diameter / 2, &t_sphere, &is_front) && t_sphere > 0 && is_front)
				{
					hit_point = vec_add(game->camera.initial_point, vec_scalar_mult(ray, t_sphere));
					distance = norm(vec_sub(game->camera.initial_point, hit_point));
					if (distance < min_distance)
					{
						min_distance = distance;
						shadow_ray = generate_ray(hit_point, game->light.initial_point);
						if (!is_in_shadow(shadow_ray, hit_point, game))
							set_color(game, x, y, 's',i);
						else
							set_color_shadow(game, x, y, 's',i);
					}
				}
				i++;
			}
			i = 0;
			while (i < game->pl_num)
			{
				if (cross_detection_ray_and_plain(ray, game->camera.initial_point, game->plain[i].normal, game->plain[i].point, &t_plain) && t_plain > 0)
				{
					hit_point = vec_add(game->camera.initial_point, vec_scalar_mult(ray, t_plain));
					distance = norm(vec_sub(game->camera.initial_point, hit_point));
					if (distance < min_distance)
					{
						min_distance = distance;
						shadow_ray = generate_ray(hit_point, game->light.initial_point);
						if (!is_in_shadow(shadow_ray, hit_point, game))
							set_color(game, x, y, 'p', i);
						else
							set_color_shadow(game, x, y, 'p', i);
					}
				}
				i++;
			}
			i = 0;
			while (i < game->cy_num)
			{
				if (cross_detection_ray_and_cylinder(ray, game->camera.initial_point, game->cylinder[i].orient, game->cylinder[i].center_point, game->cylinder[i].height, game->cylinder[i].diameter, &t_cylinder) && t_cylinder > 0)
				{
					hit_point = vec_add(game->camera.initial_point, vec_scalar_mult(ray, t_cylinder));
					distance = norm(vec_sub(game->camera.initial_point, hit_point));
					if (distance < min_distance)
					{
						min_distance = distance;
						shadow_ray = generate_ray(hit_point, game->light.initial_point);
						if (!is_in_shadow(shadow_ray, hit_point, game))
							set_color(game, x, y, 'c', i);
						else
							set_color_shadow(game, x, y, 'c', i);
					}
				}
				i++;
			}
		}
	}
	return 0;
}
