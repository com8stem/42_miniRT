/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detection_cy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutakagi <yutakagi@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 07:12:40 by yutakagi          #+#    #+#             */
/*   Updated: 2024/09/06 07:14:24 by yutakagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	evaluate_val(double A, double B, double C, double *t_val)
{
	double		D;
	double		t1;
	double		t2;
	double		temp;

	if (A < EPSILON)
		return (false);
	D = B * B - 4 * A * C;
	if (D < EPSILON)
		return (false);
	t1 = (-B - sqrt(D)) / (2 * A);
	t2 = (-B + sqrt(D)) / (2 * A);
	if (t1 > t2)
	{
		temp = t1;
		t1 = t2;
		t2 = temp;
	}
	if (t1 < EPSILON)
	{
		t1 = t2;
		if (t1 < EPSILON)
			return (false);
	}
	*t_val = t1;
	return (true);
}

static bool	intersect(t_3d_vec ray, t_3d_vec initial_point,
						t_cylinder *cy, double *t1)
{
	t_3d_vec n = vec_scalar_mult(cy->orient, 1 / norm(cy->orient));
	t_3d_vec oc = vec_sub(initial_point, cy->center_point);
	t_3d_vec cross_rn = cross_product(ray, n);
	t_3d_vec cross_ocn = cross_product(oc, n);
	
		if (!evaluate_val(norm(cross_rn) * norm(cross_rn),
			2 * dot_product(cross_rn, cross_ocn),
			norm(cross_ocn) * norm(cross_ocn) - (cy->diameter / 2.0)
			* (cy->diameter / 2.0), t1))
			return (false);
	return (true);
}

static void	set_hit_mindis(double h, double height, bool *hit,
							double *min_dis, double t1)
{
	if (h > -1 * EPSILON && h < height + EPSILON)
	{
		*min_dis = t1;
		*hit = true;
	}
	return ;
}

static void	check_bottom(double t_bottom, t_3d_vec p_bottom, t_cylinder *cy,
							bool *hit, double *min_dis)
{
	if (t_bottom > EPSILON && norm(vec_sub(p_bottom, cy->center_point))
		<= cy->diameter / 2.0)
	{
		if (t_bottom < *min_dis)
			*min_dis = t_bottom;
		*hit= true;
	}
}

static void	check_cap(double t_top, t_3d_vec p_top, t_cylinder *cy,
						bool *hit, double *min_dis)
{
	t_3d_vec n = vec_scalar_mult(cy->orient, 1 / norm(cy->orient));
	t_3d_vec top_center = vec_add(cy->center_point,
		vec_scalar_mult(n, cy->height));
	if (t_top > EPSILON && norm(vec_sub(p_top, top_center))
		<= cy->diameter / 2.0)
	{
		if (t_top < *min_dis)
			*min_dis = t_top;
		*hit =  true;
	}
	return ;
}

bool	cross_detection_ray_and_cylinder(t_3d_vec ray, t_3d_vec initial_point,
			t_cylinder *cy, double *t)
{
	bool		hit;
	double		min_dis;
	double		t1;
	t_3d_vec	n;
	double		t_bottom;

	hit = false;
	min_dis = INFINITY;
	n = vec_scalar_mult(cy->orient, 1 / norm(cy->orient));
	if (!intersect(ray, initial_point, cy, &t1))
		return (false);
	set_hit_mindis(dot_product(vec_sub(vec_add(initial_point,
		vec_scalar_mult(ray, t1)), cy->center_point), n), cy->height, &hit,
			&min_dis, t1);
	t_bottom = dot_product(vec_sub(cy->center_point, initial_point), n)
		/ dot_product(ray, n);
	check_bottom(t_bottom, vec_add(initial_point,
		vec_scalar_mult(ray, t_bottom)),cy, &hit, &min_dis);
	t_bottom = dot_product(vec_sub(vec_add(cy->center_point, vec_scalar_mult
		(n, cy->height)), initial_point), n) / dot_product(ray, n);
	t_3d_vec p_top = vec_add(initial_point, vec_scalar_mult(ray, t_bottom));
	check_cap(t_bottom, p_top, cy, &hit, &min_dis);
	*t = min_dis;
	return (hit);
}
