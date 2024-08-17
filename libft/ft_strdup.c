/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:35:53 by kishizu           #+#    #+#             */
/*   Updated: 2023/09/30 13:38:08 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dest, const char *src)
{
	char	*dest_origin;

	dest_origin = dest;
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (dest_origin);
}

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*dest;

	len = ft_strlen(s1);
	dest = (char *)malloc(len + 1);
	if (s1 == NULL)
	{
		return (NULL);
	}
	if (dest == NULL)
	{
		return (NULL);
	}
	ft_strcpy(dest, s1);
	return (dest);
}
