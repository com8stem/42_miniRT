/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:24:14 by kishizu           #+#    #+#             */
/*   Updated: 2023/10/03 20:25:53 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_over(const char *nb, long num, int sign)
{
	long	next_digit;

	if (*nb == '\0' || *nb < '0' || *nb > '9')
		return (0);
	next_digit = *nb - '0';
	if (sign > 0)
	{
		if (num > LONG_MAX / 10)
			return (1);
		if (num == LONG_MAX / 10 && next_digit > LONG_MAX % 10)
			return (1);
	}
	else if (sign < 0)
	{
		if (num * sign < LONG_MIN / 10)
			return (-1);
		if (num * sign == LONG_MIN / 10 && next_digit * sign < LONG_MIN % 10)
			return (-1);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	long	num;
	long	sign;

	num = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = sign * (-1);
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = (10 * num) + (*str - '0');
		str++;
		if (check_over(str, num, sign) == 1)
			return ((int)LONG_MAX);
		if (check_over(str, num, sign) == -1)
			return ((int)LONG_MIN);
	}
	return ((int)(num * sign));
}
