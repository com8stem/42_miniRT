/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:46:53 by kishizu           #+#    #+#             */
/*   Updated: 2023/09/25 19:16:48 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*p;

	p = NULL;
	while (*s != '\0')
	{
		if (*s == (char)c)
		{
			p = (char *)s;
		}
		s++;
	}
	if (c == '\0')
		p = (char *)s;
	return (p);
}
