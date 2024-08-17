/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:10:17 by kishizu           #+#    #+#             */
/*   Updated: 2023/09/25 17:11:59 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*dest;
	size_t			index;

	dest = b;
	index = 0;
	while (index < len)
	{
		dest[index] = (unsigned char) c;
		index++;
	}
	return (b);
}
