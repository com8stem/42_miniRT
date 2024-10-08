#include "minirt.h"

double dot_product(t_3d_vec vec1, t_3d_vec vec2)
{
	return ((vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z));
}

double norm(t_3d_vec vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_3d_vec vec_add(t_3d_vec vec1, t_3d_vec vec2)
{
    t_3d_vec result;

    result.x = vec1.x + vec2.x;
    result.y = vec1.y + vec2.y;
    result.z = vec1.z + vec2.z;

    return result;
}

t_3d_vec vec_sub(t_3d_vec vec1, t_3d_vec vec2)
{
    t_3d_vec result;

    result.x = vec1.x - vec2.x;
    result.y = vec1.y - vec2.y;
    result.z = vec1.z - vec2.z;

    return result;
}

t_3d_vec vec_scalar_mult(t_3d_vec vec, double scalar)
{
    t_3d_vec result;

    result.x = vec.x * scalar;
    result.y = vec.y * scalar;
    result.z = vec.z * scalar;

    return result;
}

t_3d_vec vec_normalize(t_3d_vec vec)
{
	double length;
	
	length = norm(vec);
	return (vec_scalar_mult(vec, 1 / length));
}

t_3d_vec cross_product(t_3d_vec v1, t_3d_vec v2)
{
	t_3d_vec result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;

	return result;
}