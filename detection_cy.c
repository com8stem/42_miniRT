/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detection_cy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 07:12:40 by yutakagi          #+#    #+#             */
/*   Updated: 2024/09/10 16:33:10 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	intersect(t_3d_vec ray, t_3d_vec initial_point, t_cylinder *cy,
		double *t1)
{
	t_3d_vec	n;
	t_3d_vec	oc;
	t_3d_vec	cross_rn;
	t_3d_vec	cross_ocn;

	n = vec_scalar_mult(cy->orient, 1 / norm(cy->orient));
	oc = vec_sub(initial_point, cy->center_point);
	cross_rn = cross_product(ray, n);
	cross_ocn = cross_product(oc, n);
	if (!evaluate_val(norm(cross_rn) * norm(cross_rn), 2 * dot_product(cross_rn,
				cross_ocn), norm(cross_ocn) * norm(cross_ocn) - (cy->diameter
				/ 2.0) * (cy->diameter / 2.0), t1))
		return (false);
	return (true);
}

static void	set_hit_mindis(double h, double height, t_cy_status *st, double t1)
{
	if (h > -1 * EPSILON && h < height + EPSILON)
	{
		st->min_dis = t1;
		st->hit = true;
	}
	return ;
}

static void	check_bottom(double t_bottom, t_3d_vec p_bottom, t_cylinder *cy,
		t_cy_status *st)
{
	if (t_bottom > EPSILON && norm(vec_sub(p_bottom,
				cy->center_point)) <= cy->diameter / 2.0)
	{
		if (t_bottom < st->min_dis)
			st->min_dis = t_bottom;
		st->hit = true;
	}
	return ;
}

static void	check_cap(double t_top, t_3d_vec p_top, t_cylinder *cy,
		t_cy_status *st)
{
	t_3d_vec	n;
	t_3d_vec	top_center;

	n = vec_scalar_mult(cy->orient, 1 / norm(cy->orient));
	top_center = vec_add(cy->center_point, vec_scalar_mult(n, cy->height));
	if (t_top > EPSILON && norm(vec_sub(p_top, top_center)) <= cy->diameter
		/ 2.0)
	{
		if (t_top < st->min_dis)
			st->min_dis = t_top;
		st->hit = true;
	}
	return ;
}

bool	cross_detection_ray_and_cylinder(t_3d_vec ray, t_3d_vec initial_point,
		t_cylinder *cy, double *t)
{
	t_cy_status	st;
	double		t_sub;
	t_3d_vec	n;
	double		t_bottom;
	t_3d_vec	p_top;

	st.hit = false;
	st.min_dis = INFINITY;
	n = vec_scalar_mult(cy->orient, 1 / norm(cy->orient));
	if (!intersect(ray, initial_point, cy, &t_sub))
		return (false);
	set_hit_mindis(dot_product(vec_sub(vec_add(initial_point,
					vec_scalar_mult(ray, t_sub)), cy->center_point), n),
		cy->height, &st, t_sub);
	t_bottom = dot_product(vec_sub(cy->center_point, initial_point), n)
		/ dot_product(ray, n);
	check_bottom(t_bottom, vec_add(initial_point, vec_scalar_mult(ray,
				t_bottom)), cy, &st);
	t_bottom = dot_product(vec_sub(vec_add(cy->center_point, vec_scalar_mult(n,
						cy->height)), initial_point), n) / dot_product(ray, n);
	p_top = vec_add(initial_point, vec_scalar_mult(ray, t_bottom));
	check_cap(t_bottom, p_top, cy, &st);
	*t = st.min_dis;
	return (st.hit);
}
