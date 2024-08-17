/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:53:53 by kishizu           #+#    #+#             */
/*   Updated: 2023/09/29 17:40:13 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;
	size_t				index;

	p = (const unsigned char *)s;
	index = 0;
	while (index < n)
	{
		if (p[index] == (unsigned char)c)
		{
			return ((void *)&p[index]);
		}
		index++;
	}
	return (NULL);
}
