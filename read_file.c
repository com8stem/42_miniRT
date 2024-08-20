#include "minirt.h"

int dummy_read_rtfile(t_rt_info *game)
{
	game->ambient_light.ratio = 0.2;
	game->ambient_light.color.r = 255;
	game->ambient_light.color.g = 255;
	game->ambient_light.color.b = 255;

	game->camera.initial_point.x = 0;
	game->camera.initial_point.y = 0;
	game->camera.initial_point.z = -5;	
	game->camera.orient.x = 0;
	game->camera.orient.y = 0;
	game->camera.orient.z = 1;
	game->camera.fov = 70;

	game->light.initial_point.x = -5;
	game->light.initial_point.y = 5.0;
	game->light.initial_point.z = -5;
	game->light.brightness = 0.6;
	game->light.color.r = 10;
	game->light.color.g = 0;
	game->light.color.b = 255;

	game->sphere.center_point.x = 0;
	game->sphere.center_point.y = 0;
	game->sphere.center_point.z = 5;
	game->sphere.diameter = 1;
	game->sphere.color.r = 0;
	game->sphere.color.g = 255;
	game->sphere.color.b = 0;

	game->plain.point.x = 0;
	game->plain.point.y = -1;
	game->plain.point.z = 0;
	game->plain.normal.x = 0;
	game->plain.normal.y = 10;
	game->plain.normal.z = 0;
	game->plain.color.r = 150;
	game->plain.color.g = 140;
	game->plain.color.b = 255;

	return (0);
}

int file_open(char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: File does not exist\n");
		exit(1);
	}
	return (fd);
}

void free_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int parse_rtfile(int fd, t_rt_info *game)
{
	char *line;
	char **split;
	char **tmp;

	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		split = ft_split(line, ' ');
		free(line);
		if (split == NULL)
			break;
		if (ft_strncmp(split[0], "A", 2) == 0)
		{
			game->ambient_light.ratio = ft_atob(split[1]);
			tmp = ft_split(split[2], ',');
			game->ambient_light.color.r = ft_atoi(tmp[0]);
			game->ambient_light.color.g = ft_atoi(tmp[1]);
			game->ambient_light.color.b = ft_atoi(tmp[2]);
			free_split(tmp);
		}
		else if (ft_strncmp(split[0], "C", 2) == 0)
		{
			tmp = ft_split(split[1], ',');
			game->camera.initial_point.x = ft_atob(tmp[0]);
			game->camera.initial_point.y = ft_atob(tmp[1]);
			game->camera.initial_point.z = ft_atob(tmp[2]);
			free_split(tmp);
			tmp = ft_split(split[2], ',');
			game->camera.orient.x = ft_atoi(tmp[0]);
			game->camera.orient.y = ft_atoi(tmp[1]);
			game->camera.orient.z = ft_atoi(tmp[2]);
			free_split(tmp);
			game->camera.fov = ft_atoi(split[3]);
		}
		else if (ft_strncmp(split[0], "L", 2) == 0)
		{
			tmp = ft_split(split[1], ',');
			game->light.initial_point.x = ft_atob(tmp[0]);
			game->light.initial_point.y = ft_atob(tmp[1]);
			game->light.initial_point.z = ft_atob(tmp[2]);
			free_split(tmp);
			game->light.brightness = ft_atob(split[2]);
			tmp = ft_split(split[3], ',');
			game->light.color.r = ft_atoi(tmp[0]);
			game->light.color.g = ft_atoi(tmp[1]);
			game->light.color.b = ft_atoi(tmp[2]);
			free_split(tmp);
		}
		else if (ft_strncmp(split[0], "sp", 3) == 0)
		{
			tmp = ft_split(split[1], ',');
			game->sphere.center_point.x = ft_atob(tmp[0]);
			game->sphere.center_point.y = ft_atob(tmp[1]);
			game->sphere.center_point.z = ft_atob(tmp[2]);
			free_split(tmp);
			game->sphere.diameter = ft_atob(split[2]);
			tmp = ft_split(split[3], ',');
			game->sphere.color.r = ft_atoi(tmp[0]);
			game->sphere.color.g = ft_atoi(tmp[1]);
			game->sphere.color.b = ft_atoi(tmp[2]);
			free_split(tmp);
		}
		else if (ft_strncmp(split[0], "pl", 3) == 0)
		{
			tmp = ft_split(split[1], ',');
			game->plain.point.x = ft_atob(tmp[0]);
			game->plain.point.y = ft_atob(tmp[1]);
			game->plain.point.z = ft_atob(tmp[2]);
			free_split(tmp);
			tmp = ft_split(split[2], ',');
			game->plain.normal.x = ft_atoi(tmp[0]);
			game->plain.normal.y = ft_atoi(tmp[1]);
			game->plain.normal.z = ft_atoi(tmp[2]);
			free_split(tmp);
			tmp = ft_split(split[3], ',');
			game->plain.color.r = ft_atoi(tmp[0]);
			game->plain.color.g = ft_atoi(tmp[1]);
			game->plain.color.b = ft_atoi(tmp[2]);
			free_split(tmp);
		}
		else if (ft_strncmp(split[0], "cy", 3) == 0)
		{
			tmp = ft_split(split[1], ',');
			game->cylinder.center_point.x = ft_atob(tmp[0]);
			game->cylinder.center_point.y = ft_atob(tmp[1]);
			game->cylinder.center_point.z = ft_atob(tmp[2]);
			free_split(tmp);
			tmp = ft_split(split[2], ',');
			game->cylinder.orient.x = ft_atoi(tmp[0]);
			game->cylinder.orient.y = ft_atoi(tmp[1]);
			game->cylinder.orient.z = ft_atoi(tmp[2]);
			free_split(tmp);
			game->cylinder.diameter = ft_atob(split[3]);
			game->cylinder.height = ft_atob(split[4]);
			tmp = ft_split(split[5], ',');
			game->cylinder.color.r = ft_atoi(tmp[0]);
			game->cylinder.color.g = ft_atoi(tmp[1]);
			game->cylinder.color.b = ft_atoi(tmp[2]);
			free_split(tmp);
		}
		free_split(split);
	}
	return (0);
}

void print_rtinfo(t_rt_info *game)
{
	printf("ambient_light.ratio: %f\n", game->ambient_light.ratio);
	printf("ambient_light.color: %d, %d, %d\n", game->ambient_light.color.r, game->ambient_light.color.g, game->ambient_light.color.b);
	printf("camera.initial_point: %f, %f, %f\n", game->camera.initial_point.x, game->camera.initial_point.y, game->camera.initial_point.z);
	printf("camera.orient: %f, %f, %f\n", game->camera.orient.x, game->camera.orient.y, game->camera.orient.z);
	printf("camera.fov: %f\n", game->camera.fov);
	printf("light.initial_point: %f, %f, %f\n", game->light.initial_point.x, game->light.initial_point.y, game->light.initial_point.z);
	printf("light.brightness: %f\n", game->light.brightness);
	printf("light.color: %d, %d, %d\n", game->light.color.r, game->light.color.g, game->light.color.b);
	printf("sphere.center_point: %f, %f, %f\n", game->sphere.center_point.x, game->sphere.center_point.y, game->sphere.center_point.z);
	printf("sphere.diameter: %f\n", game->sphere.diameter);
	printf("sphere.color: %d, %d, %d\n", game->sphere.color.r, game->sphere.color.g, game->sphere.color.b);
	printf("plain.point: %f, %f, %f\n", game->plain.point.x, game->plain.point.y, game->plain.point.z);
	printf("plain.normal: %f, %f, %f\n", game->plain.normal.x, game->plain.normal.y, game->plain.normal.z);
	printf("plain.color: %d, %d, %d\n", game->plain.color.r, game->plain.color.g, game->plain.color.b);
	printf("cylinder.center_point: %f, %f, %f\n", game->cylinder.center_point.x, game->cylinder.center_point.y, game->cylinder.center_point.z);
	printf("orient: %f, %f, %f\n", game->cylinder.orient.x, game->cylinder.orient.y, game->cylinder.orient.z);
	printf("diameter: %f\n", game->cylinder.diameter);
	printf("height: %f\n", game->cylinder.height);
	printf("color: %d, %d, %d\n", game->cylinder.color.r, game->cylinder.color.g, game->cylinder.color.b);
	return ;
}

// typedef struct s_cylinder
// {
// 	t_3d_vec center_point;
// 	t_3d_vec orient;
// 	double	diameter;
// 	double	height;
// 	t_color color;
// }	t_cylinder;

int read_rtfile(char *filename, t_rt_info *game)
{
	int fd;


	fd = file_open(filename);
	parse_rtfile(fd, game);
	print_rtinfo(game);
	close(fd);
	return (0);
}
