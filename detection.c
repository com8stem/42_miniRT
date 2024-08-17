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
