/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:10:26 by kishizu           #+#    #+#             */
/*   Updated: 2023/09/30 13:34:46 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	un;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		un = (unsigned int)-n;
	}
	else
		un = (unsigned int)n;
	if (un > 9)
	{
		ft_putnbr_fd (un / 10, fd);
	}
	ft_putchar_fd(un % 10 + '0', fd);
}
