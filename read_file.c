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

	// game->sphere.center_point.x = 0;
	// game->sphere.center_point.y = 0;
	// game->sphere.center_point.z = 5;
	// game->sphere.diameter = 1;
	// game->sphere.color.r = 0;
	// game->sphere.color.g = 255;
	// game->sphere.color.b = 0;

	// game->plain.point.x = 0;
	// game->plain.point.y = -1;
	// game->plain.point.z = 0;
	// game->plain.normal.x = 0;
	// game->plain.normal.y = 10;
	// game->plain.normal.z = 0;
	// game->plain.color.r = 150;
	// game->plain.color.g = 140;
	// game->plain.color.b = 255;

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

int count_token(char **line)
{
	int i;

	i = 0;
	while(line[i]!=NULL)
		i++;
	return (i);
}

int parse_rtfile(int fd, t_rt_info *game)
{
	char *line;
	char **split;
	char **tmp;
	int sp_count;
	int pl_count;
	int cy_count;

	sp_count = 0;
	pl_count = 0;
	cy_count = 0;
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
			if (count_token(tmp) != 3)
			{
				printf("Error: Ambient light color format is wrong\n");
				exit(1);
			}
			game->ambient_light.color.r = ft_atoi(tmp[0]);
			game->ambient_light.color.g = ft_atoi(tmp[1]);
			game->ambient_light.color.b = ft_atoi(tmp[2]);
			free_split(tmp);
		}
		else if (ft_strncmp(split[0], "C", 2) == 0)
		{
			tmp = ft_split(split[1], ',');
			if (count_token(tmp) != 3)
			{
				printf("Error: Camera initial point format is wrong\n");
				exit(1);
			}
			game->camera.initial_point.x = ft_atob(tmp[0]);
			game->camera.initial_point.y = ft_atob(tmp[1]);
			game->camera.initial_point.z = ft_atob(tmp[2]);
			free_split(tmp);
			tmp = ft_split(split[2], ',');
			if (count_token(tmp) != 3)
			{
				printf("Error: Camera orient format is wrong\n");
				exit(1);
			}
			game->camera.orient.x = ft_atoi(tmp[0]);
			game->camera.orient.y = ft_atoi(tmp[1]);
			game->camera.orient.z = ft_atoi(tmp[2]);
			free_split(tmp);
			game->camera.fov = ft_atoi(split[3]);
		}
		else if (ft_strncmp(split[0], "L", 2) == 0)
		{
			tmp = ft_split(split[1], ',');
			if (count_token(tmp) != 3)
			{
				printf("Error: Light initial point format is wrong\n");
				exit(1);
			}
			game->light.initial_point.x = ft_atob(tmp[0]);
			game->light.initial_point.y = ft_atob(tmp[1]);
			game->light.initial_point.z = ft_atob(tmp[2]);
			free_split(tmp);
			game->light.brightness = ft_atob(split[2]);
			tmp = ft_split(split[3], ',');
			if (count_token(tmp) != 3)
			{
				printf("Error: Light color format is wrong\n");
				exit(1);
			}
			game->light.color.r = ft_atoi(tmp[0]);
			game->light.color.g = ft_atoi(tmp[1]);
			game->light.color.b = ft_atoi(tmp[2]);
			free_split(tmp);
		}
		else if (ft_strncmp(split[0], "sp", 3) == 0)
		{
			tmp = ft_split(split[1], ',');
			if (count_token(tmp) != 3)
			{
				printf("Error: Sphere center point format is wrong\n");
				exit(1);
			}
			game->sphere[sp_count].center_point.x = ft_atob(tmp[0]);
			game->sphere[sp_count].center_point.y = ft_atob(tmp[1]);
			game->sphere[sp_count].center_point.z = ft_atob(tmp[2]);
			free_split(tmp);
			game->sphere[sp_count].diameter = ft_atob(split[2]);
			tmp = ft_split(split[3], ',');
			if (count_token(tmp) != 3)
			{
				printf("Error: Sphere color format is wrong\n");
				exit(1);
			}
			game->sphere[sp_count].color.r = ft_atoi(tmp[0]);
			game->sphere[sp_count].color.g = ft_atoi(tmp[1]);
			game->sphere[sp_count].color.b = ft_atoi(tmp[2]);
			free_split(tmp);
			sp_count++;
		}
		else if (ft_strncmp(split[0], "pl", 3) == 0)
		{
			tmp = ft_split(split[1], ',');
			if (count_token(tmp) != 3)
			{
				printf("Error: Plain point format is wrong\n");
				exit(1);
			}
			game->plain[pl_count].point.x = ft_atob(tmp[0]);
			game->plain[pl_count].point.y = ft_atob(tmp[1]);
			game->plain[pl_count].point.z = ft_atob(tmp[2]);
			free_split(tmp);
			tmp = ft_split(split[2], ',');
			if (count_token(tmp) != 3)
			{
				printf("Error: Plain normal format is wrong\n");
				exit(1);
			}
			game->plain[pl_count].normal.x = ft_atoi(tmp[0]);
			game->plain[pl_count].normal.y = ft_atoi(tmp[1]);
			game->plain[pl_count].normal.z = ft_atoi(tmp[2]);
			free_split(tmp);
			tmp = ft_split(split[3], ',');
			if (count_token(tmp) != 3)
			{
				printf("Error: Plain color format is wrong\n");
				exit(1);
			}
			game->plain[pl_count].color.r = ft_atoi(tmp[0]);
			game->plain[pl_count].color.g = ft_atoi(tmp[1]);
			game->plain[pl_count].color.b = ft_atoi(tmp[2]);
			free_split(tmp);
			pl_count++;
		}
		else if (ft_strncmp(split[0], "cy", 3) == 0)
		{
			tmp = ft_split(split[1], ',');
			if (count_token(tmp) != 3)
			{
				printf("Error: Cylinder center point format is wrong\n");
				exit(1);
			}
			game->cylinder[cy_count].center_point.x = ft_atob(tmp[0]);
			game->cylinder[cy_count].center_point.y = ft_atob(tmp[1]);
			game->cylinder[cy_count].center_point.z = ft_atob(tmp[2]);
			free_split(tmp);
			tmp = ft_split(split[2], ',');
			if (count_token(tmp) != 3)
			{
				printf("Error: Cylinder orient format is wrong\n");
				exit(1);
			}
			game->cylinder[cy_count].orient.x = ft_atoi(tmp[0]);
			game->cylinder[cy_count].orient.y = ft_atoi(tmp[1]);
			game->cylinder[cy_count].orient.z = ft_atoi(tmp[2]);
			free_split(tmp);
			game->cylinder[cy_count].diameter = ft_atob(split[3]);
			game->cylinder[cy_count].height = ft_atob(split[4]);
			tmp = ft_split(split[5], ',');
			if (count_token(tmp) != 3)
			{
				printf("Error: Cylinder color format is wrong\n");
				exit(1);
			}
			game->cylinder[cy_count].color.r = ft_atoi(tmp[0]);
			game->cylinder[cy_count].color.g = ft_atoi(tmp[1]);
			game->cylinder[cy_count].color.b = ft_atoi(tmp[2]);
			free_split(tmp);
			cy_count++;
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
	int i = 0;
	while (i < game->sp_num)
	{
		printf("sphere.center_point: %f, %f, %f\n", game->sphere[i].center_point.x, game->sphere[i].center_point.y, game->sphere[i].center_point.z);
		printf("sphere.diameter: %f\n", game->sphere[i].diameter);
		printf("sphere.color: %d, %d, %d\n", game->sphere[i].color.r, game->sphere[i].color.g, game->sphere[i].color.b);
		i++;
	}
	i = 0;
	while (i < game->pl_num)
	{
		printf("plain.point: %f, %f, %f\n", game->plain[i].point.x, game->plain[i].point.y, game->plain[i].point.z);
		printf("plain.normal: %f, %f, %f\n", game->plain[i].normal.x, game->plain[i].normal.y, game->plain[i].normal.z);
		printf("plain.color: %d, %d, %d\n", game->plain[i].color.r, game->plain[i].color.g, game->plain[i].color.b);
		i++;
	}
	i = 0;
	while (i < game->cy_num)
	{
		printf("cylinder.center_point: %f, %f, %f\n", game->cylinder[i].center_point.x, game->cylinder[i].center_point.y, game->cylinder[i].center_point.z);
		printf("orient: %f, %f, %f\n", game->cylinder[i].orient.x, game->cylinder[i].orient.y, game->cylinder[i].orient.z);
		printf("diameter: %f\n", game->cylinder[i].diameter);
		printf("height: %f\n", game->cylinder[i].height);
		printf("color: %d, %d, %d\n", game->cylinder[i].color.r, game->cylinder[i].color.g, game->cylinder[i].color.b);
		i++;
	}
	// printf("sphere.center_point: %f, %f, %f\n", game->sphere.center_point.x, game->sphere.center_point.y, game->sphere.center_point.z);
	// printf("sphere.diameter: %f\n", game->sphere.diameter);
	// printf("sphere.color: %d, %d, %d\n", game->sphere.color.r, game->sphere.color.g, game->sphere.color.b);
	// printf("plain.point: %f, %f, %f\n", game->plain.point.x, game->plain.point.y, game->plain.point.z);
	// printf("plain.normal: %f, %f, %f\n", game->plain.normal.x, game->plain.normal.y, game->plain.normal.z);
	// printf("plain.color: %d, %d, %d\n", game->plain.color.r, game->plain.color.g, game->plain.color.b);
	// printf("cylinder.center_point: %f, %f, %f\n", game->cylinder.center_point.x, game->cylinder.center_point.y, game->cylinder.center_point.z);
	// printf("orient: %f, %f, %f\n", game->cylinder.orient.x, game->cylinder.orient.y, game->cylinder.orient.z);
	// printf("diameter: %f\n", game->cylinder.diameter);
	// printf("height: %f\n", game->cylinder.height);
	// printf("color: %d, %d, %d\n", game->cylinder.color.r, game->cylinder.color.g, game->cylinder.color.b);
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
