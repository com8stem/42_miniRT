#include "minirt.h"

double	norm(t_3d_vec vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_3d_vec vec_add(t_3d_vec vec1, t_3d_vec vec2)
{
	t_3d_vec result;

	result.x = vec1.x + vec2.x;
	result.y = vec1.y + vec2.y;
	result.z = vec1.z + vec2.z;

	return (result);
}

t_3d_vec vec_sub(t_3d_vec vec1, t_3d_vec vec2)
{
	t_3d_vec	result;

	result.x = vec1.x - vec2.x;
	result.y = vec1.y - vec2.y;
	result.z = vec1.z - vec2.z;

	return (result);
}

t_3d_vec	vec_scalar_mult(t_3d_vec vec, double scalar)
{
	t_3d_vec	result;

	result.x = vec.x * scalar;
	result.y = vec.y * scalar;
	result.z = vec.z * scalar;

	return (result);
}

t_3d_vec	vec_normalize(t_3d_vec vec)
{
	double length;
	
	length = norm(vec);
	return (vec_scalar_mult(vec, 1 / length));
}
