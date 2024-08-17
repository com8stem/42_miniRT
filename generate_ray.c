#include "minirt.h"

t_3d_vec generate_ray(t_3d_vec initial_point, t_3d_vec target_point)
{
	t_3d_vec ray;

	ray.x = target_point.x - initial_point.x;
	ray.y = target_point.y - initial_point.y;
	ray.z = target_point.z - initial_point.z;
	return (ray);
}
