/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:59:24 by kishizu           #+#    #+#             */
/*   Updated: 2024/09/10 16:35:56 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static int	_ft_is_space(int n)
{
	if (n == ' ')
		return (1);
	return (0);
}

static double	_judge_sign(const char c, char **ptr)
{
	if (c == '-')
	{
		*ptr = *ptr + 1;
		return (-1.0);
	}
	else if (c == '+')
		*ptr = *ptr + 1;
	return (1.0);
}

double	ft_atob(char *str)
{
	double	result;
	double	sign;
	double	factor;
	int		i;

	result = 0.0;
	sign = 1.0;
	factor = 0.1;
	i = 0;
	while (_ft_is_space(str[i]))
		i++;
	sign = _judge_sign(str[i], &str);
	while (ft_isdigit(str[i]))
		result = result * 10.0 + (str[i++] - '0');
	if (str[i++] == '.')
	{
		while (ft_isdigit(str[i]))
		{
			result = result + (str[i++] - '0') * factor;
			factor *= 0.1;
		}
	}
	return (result * sign);
}
