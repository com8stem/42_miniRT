/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:13:41 by kishizu           #+#    #+#             */
/*   Updated: 2023/09/29 22:56:57 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	find_len;

	if (haystack == NULL && len == 0)
		return (NULL);
	find_len = ft_strlen(needle);
	if (*needle == '\0')
	{
		return ((char *)haystack);
	}
	while (*haystack != '\0' && len >= find_len)
	{
		if (ft_strncmp(haystack, needle, find_len) == 0)
		{
			return ((char *)haystack);
		}
		haystack++;
		len--;
	}
	return (NULL);
}
