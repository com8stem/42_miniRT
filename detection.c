#include "minirt.h"

double ft_maxb(double a, double b)
{
	if (a > b)
		return a;
	return b;
}

// bool cross_detection_ray_and_plain(t_3d_vec ray, t_3d_vec initial_point, t_3d_vec normal_plain, t_3d_vec point_on_plain)
// {
// 	double a;
// 	double b;
// 	double t;
// 	t_3d_vec s;

// 	s = generate_ray(point_on_plain, initial_point);
// 	a = dot_product(ray, normal_plain);
// 	if (a == 0)
// 		return (false);//no cross point
// 	b = dot_product(s, normal_plain);
// 	t = -b / a;
// 	if (t < 0)
// 		return (false);//no cross point
// 	return (true);//cross point
// }

bool cross_detection_ray_and_plain(t_3d_vec ray, t_3d_vec initial_point, t_3d_vec normal_plain, t_3d_vec point_on_plain, double *t)
{
    double a;
    double b;
    t_3d_vec s;

    // 平面上の点とレイの初期点のベクトルを計算
    s = vec_sub(point_on_plain, initial_point);

    // レイの方向ベクトルと平面の法線ベクトルのドット積を計算
    a = dot_product(ray, normal_plain);

    // 平行判定のために、閾値を使用
    if (fabs(a) < 1e-6)
        return false; // レイが平面と平行で交差しない場合

    // 平面上の点とレイの初期点のベクトルと法線ベクトルのドット積を計算
    b = dot_product(s, normal_plain);

    // tの値を計算
    *t = b / a;

    // tが非常に小さい場合は交差しないと判断する
    if (*t < 1e-6)
        return false; // 交点がレイの逆方向にある場合（交差しない）

    return true; // 交差する場合
}

// bool cross_detection_ray_and_sphere(t_3d_vec ray, t_3d_vec initial_point, t_3d_vec center_point, double radius)
// {
// 	double a;
// 	double b;
// 	double c;
// 	double D;
// 	double t;
// 	t_3d_vec s;

// 	s = generate_ray(center_point, initial_point);

// 	a = norm(ray) * norm(ray);
// 	b = 2 * (dot_product(s, ray));
// 	c = (norm(s) * norm(s)) - (radius * radius);
// 	D = (b * b) - (4 * a * c);
// 	if (D < 0)
// 		return (false);//no cross point
// 	t = ft_maxb(((-b + sqrt(D)) / (2 * a)), ((-b - sqrt(D)) / (2 * a)));
// 	if (t < 0)
// 		return (false);
// 	return (true);
// }


bool cross_detection_ray_and_sphere(t_3d_vec ray, t_3d_vec initial_point, t_3d_vec center_point, double radius, double *t)
{
	double a;
	double b;
	double c;
	double D;
	t_3d_vec s;

	s = generate_ray(center_point, initial_point);

	a = norm(ray) * norm(ray);
	b = 2 * (dot_product(s, ray));
	c = (norm(s) * norm(s)) - (radius * radius);
	D = (b * b) - (4 * a * c);
	if (D < 0)
		return (false); // 交差しない
	*t = ft_maxb(((-b + sqrt(D)) / (2 * a)), ((-b - sqrt(D)) / (2 * a)));
	if (*t < 0)
		return (false); // 交差しない
	return (true);
}


// double dot_product(t_3d_vec v1, t_3d_vec v2)
// {
// 	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
// }


// cross_detection_ray_and_cylinder(ray, game->camera.initial_point, game->cylinder.height, game->cylinder.diameter, &t_cylinder)
// bool cross_detection_ray_and_cylinder(t_3d_vec ray, t_3d_vec initial_point, t_3d_vec orient, t_3d_vec center_point, double height, double diameter, double *t)
// {
// 	t_3d_vec n = orient;
// 	double  A = dot_product(cross_product(ray, n), cross_product(ray, n));
// 	double B = 2 * (dot_product(cross_product(ray,n), cross_product(vec_sub(initial_point, center_point), n)));
// 	double C = dot_product(cross_product(vec_sub(initial_point, center_point), n), cross_product(vec_sub(initial_point, center_point), n)) - diameter*diameter;
// 	if (A < 1e-6)
// 		return (false);
// 	double D = B*B - 4*A*C;
// 	if (D < 0)
// 		return (false);
// 	double t1 = (-B - sqrt(D)) / (2 * A);
// 	double t2 = (-B + sqrt(D)) / (2 * A);
// 	if(*t < 0)
// 		return (false);
// 	t_3d_vec p1 = vec_add(initial_point, vec_scalar_mult(ray, t1));
// 	t_3d_vec p2 = vec_add(initial_point, vec_scalar_mult(ray, t2));
// 	if ((0 <= dot_product(vec_sub(p1, center_point), n)
// 		&& dot_product(vec_sub(p1, center_point), n) <= height)
// 		|| 
// 		(0 <= dot_product(vec_sub(p2, center_point), n)
// 		&& dot_product(vec_sub(p2, center_point), n) <= height))
// 		return (true);
// 	else
// 		return (false);
// }

// bool cross_detection_ray_and_cylinder(t_3d_vec ray, t_3d_vec initial_point, t_3d_vec orient, t_3d_vec center_point, double height, double diameter, double *t)
// {
// 	t_3d_vec n = orient;
// 	t_3d_vec oc = vec_sub(initial_point, center_point);
// 	t_3d_vec cross_rn = cross_product(ray, n);
// 	t_3d_vec cross_ocn = cross_product(oc, n);
// 	double A = dot_product(cross_rn, cross_rn);
// 	double B = 2 * dot_product(cross_rn, cross_ocn);
// 	double C = dot_product(cross_ocn, cross_ocn) - (diameter * diameter) / 4.0;

// 	if (A < 1e-6)
// 		return (false);
// 	double D = B * B - 4 * A * C;
// 	if (D < 0)
// 		return (false);
// 	double t1 = (-B - sqrt(D)) / (2 * A);
// 	double t2 = (-B + sqrt(D)) / (2 * A);
// 	if (t1 > t2)
// 		t1 = t2;
// 	if (t1 < 0)
// 		return (false);
// 	t_3d_vec p = vec_add(initial_point, vec_scalar_mult(ray, t1));
// 	double h = dot_product(vec_sub(p, center_point), n);
// 	if (h < 0 || h > height)
// 		return (false);
// 	*t = t1;
// 	return (true);
// }


bool cross_detection_ray_and_cylinder(t_3d_vec ray, t_3d_vec initial_point, t_3d_vec orient, t_3d_vec center_point, double height, double diameter, double *t)
{
	t_3d_vec n = orient;
	t_3d_vec oc = vec_sub(initial_point, center_point);
	t_3d_vec cross_rn = cross_product(ray, n);
	t_3d_vec cross_ocn = cross_product(oc, n);
	double A = dot_product(cross_rn, cross_rn);
	double B = 2 * dot_product(cross_rn, cross_ocn);
	double C = dot_product(cross_ocn, cross_ocn) - (diameter * diameter) / 4.0;

	if (A < 1e-6)
		return (false);
	double D = B * B - 4 * A * C;
	if (D < 0)
		return (false);
	double t1 = (-B - sqrt(D)) / (2 * A);
	double t2 = (-B + sqrt(D)) / (2 * A);
	if (t1 > t2)
		t1 = t2;
	if (t1 < 0)
		return (false);
	t_3d_vec p = vec_add(initial_point, vec_scalar_mult(ray, t1));
	double h = dot_product(vec_sub(p, center_point), n);
	if (h < 0 || h > height)
	{
		// Check bottom cap
		t_3d_vec bottom_center = vec_add(center_point, vec_scalar_mult(n, 0));
		double t_bottom = dot_product(vec_sub(bottom_center, initial_point), n) / dot_product(ray, n);
		t_3d_vec p_bottom = vec_add(initial_point, vec_scalar_mult(ray, t_bottom));
		if (t_bottom >= 0 && norm(vec_sub(p_bottom, bottom_center)) <= diameter / 2.0)
		{
			*t = t_bottom;
			return (true);
		}
		// Check top cap
		t_3d_vec top_center = vec_add(center_point, vec_scalar_mult(n, height));
		double t_top = dot_product(vec_sub(top_center, initial_point), n) / dot_product(ray, n);
		t_3d_vec p_top = vec_add(initial_point, vec_scalar_mult(ray, t_top));
		if (t_top >= 0 && norm(vec_sub(p_top, top_center)) <= diameter / 2.0)
		{
			*t = t_top;
			return (true);
		}
		return (false);
	}
	*t = t1;
	return (true);
}
