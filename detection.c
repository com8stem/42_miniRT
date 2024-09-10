/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 06:29:54 by yutakagi          #+#    #+#             */
/*   Updated: 2024/09/10 16:00:59 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	cross_detection_ray_and_plain(t_3d_vec ray, t_3d_vec initial_point,
		t_plain *pl, double *t)
{
	double		a;
	double		b;
	t_3d_vec	s;

	s = vec_sub(pl->point, initial_point);
	a = dot_product(ray, pl->normal);
	if (fabs(a) < EPSILON)
		return (false);
	b = dot_product(s, pl->normal);
	*t = b / a;
	if (*t < EPSILON)
		return (false);
	return (true);
}

bool	cross_detection_ray_and_sphere(t_3d_vec ray, t_3d_vec initial_point,
		t_sphere *sp, t_detect_status *st)
{
	double		a;
	double		b;
	double		c;
	double		D;
	t_3d_vec	s;

	s = generate_ray(sp->center_point, initial_point);
	a = norm(ray) * norm(ray);
	if (a < EPSILON)
		return (false);
	b = 2 * (dot_product(s, ray));
	c = (norm(s) * norm(s)) - ((sp->diameter * sp->diameter) / 4.0);
	D = (b * b) - (4 * a * c);
	if (D < EPSILON)
		return (false);
	if ((-b - sqrt(D)) / (2 * a) > EPSILON)
		st->t_sphere = (-b - sqrt(D)) / (2 * a);
	else if ((-b + sqrt(D)) / (2 * a) > EPSILON)
		st->t_sphere = (-b + sqrt(D)) / (2 * a);
	else
		return (false);
	st->is_front = (dot_product(ray,
				vec_normalize(vec_sub(vec_add(initial_point,
							vec_scalar_mult(ray, st->t)),
						sp->center_point))) < 0);
	return (true);
}
