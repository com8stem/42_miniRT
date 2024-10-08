#include "minirt.h"

bool is_in_shadow(t_3d_vec shadow_ray, t_3d_vec hit_point, t_rt_info *game)
{
	double t;

	if (cross_detection_ray_and_sphere(shadow_ray, hit_point, game->sphere.center_point, game->sphere.diameter / 2, &t) && t > 0)
		return (true);
	if (cross_detection_ray_and_plain(shadow_ray, hit_point, game->plain.normal, game->plain.point, &t) && t > 0)
		return (true);
	if (cross_detection_ray_and_cylinder(shadow_ray, hit_point,game->cylinder.orient, game->cylinder.center_point, game->cylinder.height, game->cylinder.diameter, &t) && t > 0)
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
// 			ray = generate_ray(game->camera.initial_point, convert_screen_points(x, y));
// 			if (cross_detection_ray_and_sphere(ray, game->camera.initial_point, game->sphere.center_point, game->sphere.diameter / 2))			
// 				game->color_map[y][x] = 0x0000FF;
// 			else if (cross_detection_ray_and_plain(ray, game->camera.initial_point, game->plain.normal, game->plain.point))
// 				game->color_map[y][x] = 0x00FF00;
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (0);
// }


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
// 			ray = generate_ray(game->camera.initial_point, convert_screen_points(x, y));

// 			double t_sphere;
// 			double t_plain;
// 			double t_cylinder;
// 			t_3d_vec hit_point;
// 			t_3d_vec shadow_ray;
// 			double distance;

// 			distance = 0;
// 			if (cross_detection_ray_and_sphere(ray, game->camera.initial_point, game->sphere.center_point, game->sphere.diameter / 2, &t_sphere))
// 			{
// 				hit_point = vec_add(game->camera.initial_point, vec_scalar_mult(ray, t_sphere));
// 				distance = norm(vec_sub(game->initial_point, hit_point));
// 				shadow_ray = generate_ray(hit_point, game->light.initial_point);
// 				if (!is_in_shadow(shadow_ray, hit_point, game))
// 					game->color_map[y][x] = 0x0000FF;
// 				else
// 					game->color_map[y][x] = 0x000088; //shadow
// 			}
// 			else if (cross_detection_ray_and_plain(ray, game->camera.initial_point, game->plain.normal, game->plain.point, &t_plain))
// 			{
// 				hit_point = vec_add(game->camera.initial_point, vec_scalar_mult(ray, t_plain));
// 				shadow_ray = generate_ray(hit_point, game->light.initial_point);
// 				if (!is_in_shadow(shadow_ray, hit_point, game))
// 					game->color_map[y][x] = 0x00FF00;
// 				else
// 					game->color_map[y][x] = 0x008800;//shadow
// 			}
// 			else if (cross_detection_ray_and_cylinder(ray, game->camera.initial_point,game->cylinder.orient, game->cylinder.center_point, game->cylinder.height, game->cylinder.diameter, &t_cylinder))
// 			{
// 				hit_point = vec_add(game->camera.initial_point, vec_scalar_mult(ray, t_cylinder));
// 				shadow_ray = generate_ray(hit_point, game->light.initial_point);
// 				if (!is_in_shadow(shadow_ray, hit_point, game))
// 					game->color_map[y][x] = 0xFF0000;
// 				else
// 					game->color_map[y][x] = 0x000088;//shadow	
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (0);
// }



int convert_rgb_to_hex(int r, int g, int b)
{
	return ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF);
}

void set_color(t_rt_info *game, int x, int y, t_3d_vec hit_point, char object_type)
{
	int color;

	if (object_type == 's')
		color = convert_rgb_to_hex(game->sphere.color.r, game->sphere.color.g, game->sphere.color.b);
	else if (object_type == 'p')
		color = convert_rgb_to_hex(game->plain.color.r, game->plain.color.g, game->plain.color.b);
	else if (object_type == 'c')
		color = convert_rgb_to_hex(game->cylinder.color.r, game->cylinder.color.g, game->cylinder.color.b);
	else
		color = 0x888888;
	game->color_map[y][x] = color;
}

int set_color_map(t_rt_info *game)
{
	int x, y;
	t_3d_vec ray;
	double min_distance, distance;
	double t_sphere, t_plain, t_cylinder;
	t_3d_vec hit_point, shadow_ray;

	for (y = 0; y < HEIGHT; y++)
	{
		for (x = 0; x < WIDTH; x++)
		{
			game->color_map[y][x] = 0x888888;
			ray = generate_ray(game->camera.initial_point, convert_screen_points(x, y));
			min_distance = INFINITY;
			if (cross_detection_ray_and_sphere(ray, game->camera.initial_point, game->sphere.center_point, game->sphere.diameter / 2, &t_sphere))
			{
				hit_point = vec_add(game->camera.initial_point, vec_scalar_mult(ray, t_sphere));
				distance = norm(vec_sub(game->camera.initial_point, hit_point));
				if (distance < min_distance)
				{
					min_distance = distance;
					shadow_ray = generate_ray(hit_point, game->light.initial_point);
					if (!is_in_shadow(shadow_ray, hit_point, game))
						// game->color_map[y][x] = 0x0000FF;
						set_color(game, x, y, hit_point, 's');
					else
						game->color_map[y][x] = 0x000088; // shadow
				}
			}
			if (cross_detection_ray_and_plain(ray, game->camera.initial_point, game->plain.normal, game->plain.point, &t_plain))
			{
				hit_point = vec_add(game->camera.initial_point, vec_scalar_mult(ray, t_plain));
				distance = norm(vec_sub(game->camera.initial_point, hit_point));
				if (distance < min_distance)
				{
					min_distance = distance;
					shadow_ray = generate_ray(hit_point, game->light.initial_point);
					if (!is_in_shadow(shadow_ray, hit_point, game))
						// game->color_map[y][x] = 0x00FF00;
						set_color(game, x, y, hit_point, 'p');
					else
						game->color_map[y][x] = 0x008800; // shadow
				}
			}

			if (cross_detection_ray_and_cylinder(ray, game->camera.initial_point, game->cylinder.orient, game->cylinder.center_point, game->cylinder.height, game->cylinder.diameter, &t_cylinder))
			{
				hit_point = vec_add(game->camera.initial_point, vec_scalar_mult(ray, t_cylinder));
				distance = norm(vec_sub(game->camera.initial_point, hit_point));
				if (distance < min_distance)
				{
					min_distance = distance;
					shadow_ray = generate_ray(hit_point, game->light.initial_point);
					if (!is_in_shadow(shadow_ray, hit_point, game))
						// game->color_map[y][x] = 0xFF0000;
						 set_color(game, x, y, hit_point, 'c');
					else
						game->color_map[y][x] = 0x880000; // shadow
				}
			}
		}
	}
	return 0;
}


// bool cross_detection_ray_and_cylinder(t_3d_vec ray, t_3d_vec initial_point, t_3d_vec center_point, t_3d_vec height,  double diameter, 
// double height, double *t)
// typedef struct s_cylinder
// {
// 	t_3d_vec center_point;
// 	t_3d_vec orient;
// 	double	diameter;
// 	double	height;
// 	t_color color;
// }	t_cylinder;