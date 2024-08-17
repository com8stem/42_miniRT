/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:33:57 by kishizu           #+#    #+#             */
/*   Updated: 2023/09/29 17:41:39 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				index;

	d = dst;
	s = src;
	index = 0;
	if (dst != NULL || src != NULL)
	{
		while (index < n)
		{
			d[index] = s[index];
			index++;
		}
	}
	return (dst);
}
