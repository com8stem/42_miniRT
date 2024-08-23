#include "minirt.h"

t_3d_vec	convert_screen_points(int x, int y, double fov)
{
	t_3d_vec	converted_point;

	converted_point.x = (2.0 * (double)x) / ((double)WIDTH - 1) - 1.0;
	converted_point.y = 1.0 - (2.0 * (double)y / (HEIGHT - 1));
	converted_point.z = 0;
	fov = 70;
	return (converted_point);
}

// t_3d_vec convert_screen_points(int x, int y, double fov)
// {
// 	t_3d_vec converted_point;
// 	double aspect_ratio = (double)WIDTH / (double)HEIGHT;
// 	double scale = tan(fov * 0.5 * 3.14159 / 180.0);

// 	converted_point.x = (2.0 * (double)x / (double)WIDTH - 1.0) * aspect_ratio * scale;
// 	converted_point.y = (1.0 - 2.0 * (double)y / (double)HEIGHT) * scale;
// 	converted_point.z = 0;

// 	return converted_point;
// }