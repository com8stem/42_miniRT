/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:00:57 by kishizu           #+#    #+#             */
/*   Updated: 2023/09/30 13:45:09 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*mem;

	if (s == NULL)
		return (NULL);
	if ((unsigned int)ft_strlen(s) < start)
		len = 0;
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	mem = malloc(sizeof(char) * (len + 1));
	if (mem == NULL)
		return (NULL);
	ft_strlcpy(mem, s + start, len + 1);
	return (mem);
}
