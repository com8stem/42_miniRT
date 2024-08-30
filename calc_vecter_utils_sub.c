#include "minirt.h"

t_3d_vec	cross_product(t_3d_vec v1, t_3d_vec v2)
{
	t_3d_vec result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;

	return result;
}

double	dot_product(t_3d_vec vec1, t_3d_vec vec2)
{
	return ((vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z));
}