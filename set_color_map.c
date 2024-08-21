#include "minirt.h"

#ifndef SHADOW_COLOR
#define SHADOW_COLOR 0x222222
#define SHADOW_FACTOR 0.5
#define BACKGROUND_COLOR 0x000000
#endif

bool is_in_shadow(t_3d_vec shadow_ray, t_3d_vec hit_point, t_rt_info *game)
{
	double t;
	int j;

	return (false);
	j = 0;
	while (j < game->sp_num)
	{
		if (cross_detection_ray_and_sphere(shadow_ray, hit_point, game->sphere[j].center_point, game->sphere[j].diameter / 2, &t) && t > 0 )
			return (true);
		j++;
	}
	j = 0;
	while (j < game->pl_num)
	{
		if (cross_detection_ray_and_plain(shadow_ray, hit_point, game->plain[j].normal, game->plain[j].point, &t) && t > 0 )
			return (true);
		j++;
	}
	j = 0;
	while (j < game->cy_num)
	{
		if (cross_detection_ray_and_cylinder(shadow_ray, hit_point, game->cylinder[j].orient, game->cylinder[j].center_point, game->cylinder[j].height, game->cylinder[j].diameter, &t) && t > 0)
			return (true);
		j++;
	}
	return false;
}

int convert_rgb_to_hex(int r, int g, int b)
{
	return ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF);
}

void set_color(t_rt_info *game, int x, int y, char object_type, int i)
{
	int color;

	if (object_type == 's')
		color = convert_rgb_to_hex(game->sphere[i].color.r, game->sphere[i].color.g, game->sphere[i].color.b);
	else if (object_type == 'p')
		color = convert_rgb_to_hex(game->plain[i].color.r, game->plain[i].color.g, game->plain[i].color.b);
	else if (object_type == 'c')
		color = convert_rgb_to_hex(game->cylinder[i].color.r, game->cylinder[i].color.g, game->cylinder[i].color.b);
	else
		color = BACKGROUND_COLOR;
	game->color_map[y][x] = color;
}

int convert_rgb_to_hex_shadow(int r, int g, int b)
{
	r = (int)(r * SHADOW_FACTOR);
	g = (int)(g * SHADOW_FACTOR);
	b = (int)(b * SHADOW_FACTOR);

	return ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF);
}


void set_color_shadow(t_rt_info *game, int x, int y, char object_type, int i)
{
	int color;

	if (object_type == 's')
		color = convert_rgb_to_hex_shadow(game->sphere[i].color.r, game->sphere[i].color.g, game->sphere[i].color.b);
	else if (object_type == 'p')
		color = convert_rgb_to_hex_shadow(game->plain[i].color.r, game->plain[i].color.g, game->plain[i].color.b);
	else if (object_type == 'c')
		color = convert_rgb_to_hex_shadow(game->cylinder[i].color.r, game->cylinder[i].color.g, game->cylinder[i].color.b);
	else
		color = BACKGROUND_COLOR;
	game->color_map[y][x] = color;
}


int set_color_map(t_rt_info *game)
{
	int x, y;
	t_3d_vec ray;
	double min_distance, distance;
	double t_sphere, t_plain, t_cylinder;
	t_3d_vec hit_point, shadow_ray;
	int i;

	for (y = 0; y < HEIGHT; y++)
	{
		for (x = 0; x < WIDTH; x++)
		{
			game->color_map[y][x] = BACKGROUND_COLOR;
			ray = generate_ray(game->camera.initial_point, convert_screen_points(x, y, game->camera.fov));
			i = 0;
			while (i < game->sp_num)
			{
				min_distance = INFINITY;
				if (cross_detection_ray_and_sphere(ray, game->camera.initial_point, game->sphere[i].center_point, game->sphere[i].diameter / 2, &t_sphere) && t_sphere > 0)
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
							set_color_shadow(game, x, y, 's',i); // shadow
					}
				}
				i++;
			}
			i = 0;
			while (i < game->pl_num)
			{
				min_distance = INFINITY;
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
				min_distance = INFINITY;
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