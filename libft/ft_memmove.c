/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:39:20 by kishizu           #+#    #+#             */
/*   Updated: 2023/10/03 19:47:51 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	move_tofrom(const unsigned char *from, unsigned char *to, size_t n)
{
	size_t	i;

	i = n - 1;
	while (i > 0)
	{
		to[i] = from[i];
		i--;
	}
	to[i] = from[i];
}

void	move_fromto(const unsigned char *from, unsigned char *to, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		to[i] = from[i];
		i++;
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const unsigned char	*from;
	unsigned char		*to;

	to = (unsigned char *)dst;
	from = (const unsigned char *)src;
	if (to > from && (size_t)(to - from) < len)
	{
		move_tofrom(from, to, len);
	}
	else if (from > to && (size_t)(from - to) < len)
	{
		move_fromto(from, to, len);
	}
	else
		ft_memcpy(to, from, len);
	return (dst);
}
