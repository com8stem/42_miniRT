#include "minirt.h"

int start_up_window(t_rt_info *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "miniRT");
	game->img_data->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img_data->addr = mlx_get_data_addr(game->img_data->img, &(game->img_data->bits_per_pixel), &(game->img_data->line_length), &(game->img_data->endian));
	return (0);
}

int close_window(void)
{
	exit(0);
}

int key_hook(int keycode, t_rt_info *game)
{
	(void)game;
	if (keycode == KEY_ESC)
		close_window();
	return (0);
}

void set_loop_hook(t_rt_info *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_hook, game);
	mlx_hook(game->win, 17, 1L << 17, close_window, game);
}
