/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:59:50 by kishizu           #+#    #+#             */
/*   Updated: 2024/09/10 15:59:57 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	my_mlx_pixel_put(t_imgdata *img, int x, int y, int color)
{
	char	*dst;

	if (!(x >= WIDTH || y >= HEIGHT || x < 0 || y < 0))
	{
		dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel
					/ 8));
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

static void	_initialize_shape(t_rt_info *game)
{
	game->sphere = x_ft_calloc(game->sp_num, sizeof(t_sphere));
	game->plain = x_ft_calloc(game->pl_num, sizeof(t_plain));
	game->cylinder = x_ft_calloc(game->cy_num, sizeof(t_cylinder));
}

// __attribute__((destructor))
// static void destructor() {
// 	system("leaks -q a.out");
// }

int	main(int argc, char **argv)
{
	static t_rt_info	game;
	t_imgdata			img;

	game.img_data = &img;
	check_argc(argc);
	check_filename(argv[1]);
	check_fileformat(argv[1], &game);
	_initialize_shape(&game);
	read_rtfile(argv[1], &game);
	start_up_window(&game);
	set_color_map(&game);
	drow_image(&game);
	set_loop_hook(&game);
	mlx_put_image_to_window(game.mlx, game.win, game.img_data->img, 0, 0);
	mlx_loop(game.mlx);
	return (0);
}
