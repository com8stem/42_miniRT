/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:59:29 by kishizu           #+#    #+#             */
/*   Updated: 2024/09/10 15:59:37 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_3d_vec	generate_ray(t_3d_vec initial_point, t_3d_vec target_point)
{
	t_3d_vec	ray;

	ray.x = target_point.x - initial_point.x;
	ray.y = target_point.y - initial_point.y;
	ray.z = target_point.z - initial_point.z;
	return (ray);
}
