#include "minirt.h"

void	my_mlx_pixel_put(t_imgdata *img, int x, int y, int color)
{
	char	*dst;

	if (!(x >= WIDTH || y >= HEIGHT || x < 0 || y < 0))
	{
		dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	drow_image(t_rt_info *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(game->img_data, x, y, game->color_map[y][x]);
			x++;
		}
		y++;
	}
}

__attribute__((destructor))
static void destructor() {
	system("leaks -q a.out");
}

void initialize_shape(t_rt_info *game)
{
	int i;

	game->sphere = malloc(sizeof(t_sphere) * game->sp_num);
	game->plain = malloc(sizeof(t_plain) * game->pl_num);
	game->cylinder = malloc(sizeof(t_cylinder) * game->cy_num);
	i = 0;
	while (i < game->sp_num)
	{
		game->sphere[i].center_point = (t_3d_vec){0, 0, 0};
		game->sphere[i].diameter = 0;
		game->sphere[i].color = (t_color){0, 0, 0};
		i++;
	}
	i = 0;
	while (i < game->pl_num)
	{
		game->plain[i].point = (t_3d_vec){0, 0, 0};
		game->plain[i].normal = (t_3d_vec){0, 0, 0};
		game->plain[i].color = (t_color){0, 0, 0};
		i++;
	}
	i = 0;
	while (i < game->cy_num)
	{
		game->cylinder[i].center_point = (t_3d_vec){0, 0, 0};
		game->cylinder[i].orient = (t_3d_vec){0, 0, 0};
		game->cylinder[i].diameter = 0;
		game->cylinder[i].height = 0;
		game->cylinder[i].color = (t_color){0, 0, 0};
		i++;
	}
}


int	main(int argc, char **argv)
{
	static t_rt_info	game;
	t_imgdata			img;

	game.img_data = &img;
	check_argc(argc);
	check_filename(argv[1]);
	check_fileformat(argv[1], &game);
	initialize_shape(&game);
	read_rtfile(argv[1], &game);
	start_up_window(&game);
	set_color_map(&game);
	drow_image(&game);
	set_loop_hook(&game);
	mlx_put_image_to_window(game.mlx, game.win, game.img_data->img, 0, 0);
	mlx_loop(game.mlx);
	return (0);
}
