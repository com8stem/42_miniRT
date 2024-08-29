#include "minirt.h"

int	apply_ambient(t_rt_info *game, int color)
{
	int	r;
	int	g;
	int	b;
	int	final_color;

	r = (int)(game->ambient_light.ratio * game->ambient_light.color.r);
	g = (int)(game->ambient_light.ratio * game->ambient_light.color.g);
	b = (int)(game->ambient_light.ratio * game->ambient_light.color.b);
	r = r + ((color >> 16) & 0xFF);
	g = g + ((color >> 8) & 0xFF);
	b = b + (color & 0xFF);
	 if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	final_color = (r << 16) | (g << 8) | b;
	return (final_color);
}

int	convert_rgb_to_hex_shadow(int r, int g, int b)
{
	r = (int)(r * SHADOW_FACTOR);
	g = (int)(g * SHADOW_FACTOR);
	b = (int)(b * SHADOW_FACTOR);

	return ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF);
}

int	convert_rgb_to_hex(int r, int g, int b)
{
	return ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF);
}