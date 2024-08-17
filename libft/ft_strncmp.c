/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:49:47 by kishizu           #+#    #+#             */
/*   Updated: 2023/09/29 22:59:56 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			index;
	unsigned char	*us1;
	unsigned char	*us2;

	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	index = 0;
	if (n == 0)
		return (0);
	while (us1[index] != '\0' && us2[index] != '\0' && index + 1 < n)
	{
		if (us1[index] != us2[index])
		{
			return ((int)(us1[index] - us2[index]));
		}
		index++;
	}
	return ((int)(us1[index] - us2[index]));
}
