#include "minirt.h"

t_3d_vec	convert_screen_points(int x, int y)
{
	t_3d_vec	converted_point;

	converted_point.x = (2.0 * (double)x) / ((double)WIDTH - 1) - 1.0;
	converted_point.y = 1.0 - (2.0 * (double)y / (HEIGHT - 1));
	converted_point.z = 0;
	return (converted_point);
}