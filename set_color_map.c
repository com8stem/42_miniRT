#include "minirt.h"

bool is_in_shadow(t_3d_vec shadow_ray, t_3d_vec hit_point, t_rt_info *game)
{
	double t;

	if (cross_detection_ray_and_sphere(shadow_ray, hit_point, game->sphere.center_point, game->sphere.diameter / 2, &t) && t > 0)
		return (true);
	if (cross_detection_ray_and_plain(shadow_ray, hit_point, game->plain.normal, game->plain.point, &t) && t > 0)
		return (true);
	return false;
}

// int set_color_map(t_rt_info *game)
// {
// 	int x;
// 	int y;
// 	t_3d_vec ray;

// 	y = 0;
// 	while (y < HEIGHT)
// 	{
// 		x = 0;
// 		while (x < WIDTH)
// 		{
// 			game->color_map[y][x] = 0x888888;
// 			ray = generate_ray(game->camera.initilal_point, convert_screen_points(x, y));
// 			if (cross_detection_ray_and_sphere(ray, game->camera.initilal_point, game->sphere.center_point, game->sphere.diameter / 2))			
// 				game->color_map[y][x] = 0x0000FF;
// 			else if (cross_detection_ray_and_plain(ray, game->camera.initilal_point, game->plain.normal, game->plain.point))
// 				game->color_map[y][x] = 0x00FF00;
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (0);
// }


int set_color_map(t_rt_info *game)
{
	int x;
	int y;
	t_3d_vec ray;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			game->color_map[y][x] = 0x888888;
			ray = generate_ray(game->camera.initilal_point, convert_screen_points(x, y));

			double t_sphere;
			double t_plain;
			t_3d_vec hit_point;
			t_3d_vec shadow_ray;

			if (cross_detection_ray_and_sphere(ray, game->camera.initilal_point, game->sphere.center_point, game->sphere.diameter / 2, &t_sphere))
			{
				hit_point = vec_add(game->camera.initilal_point, vec_scalar_mult(ray, t_sphere));
				shadow_ray = generate_ray(hit_point, game->light.initilal_point);
				if (!is_in_shadow(shadow_ray, hit_point, game))
					game->color_map[y][x] = 0x0000FF;
				else
					game->color_map[y][x] = 0x000088; //shadow
			}
			else if (cross_detection_ray_and_plain(ray, game->camera.initilal_point, game->plain.normal, game->plain.point, &t_plain))
			{
				hit_point = vec_add(game->camera.initilal_point, vec_scalar_mult(ray, t_plain));
				shadow_ray = generate_ray(hit_point, game->light.initilal_point);
				if (!is_in_shadow(shadow_ray, hit_point, game))
					game->color_map[y][x] = 0x00FF00;
				else
					game->color_map[y][x] = 0x008800;//shadow
			}
			x++;
		}
		y++;
	}
	return (0);
}
