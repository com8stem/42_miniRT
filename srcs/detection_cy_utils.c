/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detection_cy_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:32:29 by kishizu           #+#    #+#             */
/*   Updated: 2024/09/10 16:34:14 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

bool	evaluate_val(double a, double b, double c, double *t_val)
{
	double	t1;
	double	t2;
	double	temp;

	if (a < EPSILON)
		return (false);
	if (b * b - 4 * a * c < EPSILON)
		return (false);
	t1 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
	t2 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
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
