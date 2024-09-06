/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yutakagi <yutakagi@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 06:29:54 by yutakagi          #+#    #+#             */
/*   Updated: 2024/09/06 07:12:56 by yutakagi         ###   ########.fr       */
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
