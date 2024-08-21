#include "minirt.h"

void my_mlx_pixel_put(t_imgdata *img, int x, int y, int color)
{
	char *dst;

	if (!(x >= WIDTH || y >= HEIGHT || x < 0 || y < 0))
	{
		dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void drow_image(t_rt_info *game)
{
	int x;
	int y;

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


int main(int argc, char **argv)
{
	static t_rt_info game;
	t_imgdata img;

	game.img_data = &img;
	check_argc(argc);
	check_filename(argv[1]);
	check_fileformat(argv[1]);
	read_rtfile(argv[1], &game);
	// dummy_read_rtfile(&game);
	start_up_window(&game);
	set_color_map(&game);
	drow_image(&game);
	set_loop_hook(&game);
	mlx_put_image_to_window(game.mlx, game.win, game.img_data->img, 0, 0);
	mlx_loop(game.mlx);
	return (0);
}
