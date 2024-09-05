/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutakagi <yutakagi@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 06:29:54 by yutakagi          #+#    #+#             */
/*   Updated: 2024/09/04 10:40:09 by yutakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	cross_detection_ray_and_plain(t_3d_vec ray, t_3d_vec initial_point,
			t_3d_vec normal_plain, t_3d_vec point_on_plain, double *t)
{
	double		a;
	double		b;
	t_3d_vec	s;

	s = vec_sub(point_on_plain, initial_point);
	a = dot_product(ray, normal_plain);
	if (fabs(a) < EPSILON)
		return (false);
	b = dot_product(s, normal_plain);
	*t = b / a;
	if (*t < EPSILON)
		return (false);
	return (true);
}

bool	cross_detection_ray_and_sphere(t_3d_vec ray, t_3d_vec initial_point,
			t_3d_vec center_point,double radius, double *t, bool *is_front)
{
	double		a;
	double		b;
	double		c;
	double		D;
	t_3d_vec	s;

	s = generate_ray(center_point, initial_point);
	a = norm(ray) * norm(ray);
	if (a < EPSILON)
		return (false);
	b = 2 * (dot_product(s, ray));
	c = (norm(s) * norm(s)) - (radius * radius);
	D = (b * b) - (4 * a * c);
	if (D < EPSILON)
		return (false);
	if ((-b - sqrt(D)) / (2 * a) > EPSILON)
		*t = (-b - sqrt(D)) / (2 * a);
	else if ((-b + sqrt(D)) / (2 * a) > EPSILON)
		*t = (-b + sqrt(D)) / (2 * a);
	else
		return (false);
	*is_front = (dot_product(ray, vec_normalize(vec_sub(vec_add(initial_point,
		vec_scalar_mult(ray, *t)), center_point))) < 0);
	return (true);
}

// static bool	evaluate_val(double A, double B, double C, double *t_val)
// {
// 	double		D;
// 	double t1;
// 	double t2;
// 	double temp;

// 	if (A < EPSILON)
// 		return (false);
// 	D = B * B - 4 * A * C;
// 	if (D < EPSILON)
// 		return (false);
// 	t1 = (-B - sqrt(D)) / (2 * A);
// 	t2 = (-B + sqrt(D)) / (2 * A);
// 	if (t1 > t2)
// 	{
// 		temp = t1;
// 		t1 = t2;
// 		t2 = temp;
// 	}
// 	if (t1 < EPSILON)
// 	{
// 		t1 = t2;
// 		if (t1 < EPSILON)
// 			return (false);
// 	}
// 	*t_val = t1;
// 	return (true);
// }

bool	cross_detection_ray_and_cylinder(t_3d_vec ray, t_3d_vec initial_point,
	t_3d_vec orient, t_3d_vec center_point, double height, double diameter, double *t)
{
	t_3d_vec n = vec_scalar_mult(orient, 1 / norm(orient));
	t_3d_vec oc = vec_sub(initial_point, center_point);
	t_3d_vec cross_rn = cross_product(ray, n);
	t_3d_vec cross_ocn = cross_product(oc, n);
	double A = dot_product(cross_rn, cross_rn);
	double B = 2 * dot_product(cross_rn, cross_ocn);
	double C = dot_product(cross_ocn, cross_ocn) - (diameter * diameter) / 4.0;
	bool hit  = false;
	double min_dis = INFINITY;

	if (A < EPSILON)
		return (false);
	double D = B * B - 4 * A * C;
	if (D <  EPSILON)
		return (false);
	double t1 = (-B - sqrt(D)) / (2 * A);
	double t2 = (-B + sqrt(D)) / (2 * A);
	if (t1 > t2)
	{
		double temp = t1;
		t1 = t2;
		t2 = temp;
	}
	if (t1 < EPSILON)
	{
		t1 = t2;
		if (t1 < EPSILON)
			return false;
	}
	t_3d_vec p = vec_add(initial_point, vec_scalar_mult(ray, t1));
	double h = dot_product(vec_sub(p, center_point), n);
	if (h > -1 * EPSILON && h < height + EPSILON)
	{
		min_dis = t1;
		hit = true;
	}
	double t_bottom = dot_product(vec_sub(center_point, initial_point), n) / dot_product(ray, n);
	t_3d_vec p_bottom = vec_add(initial_point, vec_scalar_mult(ray, t_bottom));
	if (t_bottom > EPSILON && norm(vec_sub(p_bottom, center_point)) <= diameter / 2.0)
	{
		if (t_bottom < min_dis)
			min_dis = t_bottom;
		hit= true;
	}
	t_3d_vec top_center = vec_add(center_point, vec_scalar_mult(n, height));
	double t_top = dot_product(vec_sub(top_center, initial_point), n) / dot_product(ray, n);
	t_3d_vec p_top = vec_add(initial_point, vec_scalar_mult(ray, t_top));
	if (t_top > EPSILON && norm(vec_sub(p_top, top_center)) <= diameter / 2.0)
	{
		if (t_top < min_dis)
			min_dis = t_top;
		hit =  true;
	}
	*t = min_dis;
	return (hit);
}
