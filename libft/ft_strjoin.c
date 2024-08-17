/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:13:51 by kishizu           #+#    #+#             */
/*   Updated: 2023/11/29 20:24:06 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		total_len;
	char	*result;

	total_len = ft_strlen(s1) + ft_strlen(s2);
	if (total_len == 0)
		return (NULL);
	result = (char *)malloc(total_len + 1);
	if (result == NULL)
		return (NULL);
	if (s1 == NULL && s2 != NULL)
		ft_strlcpy (result, s2, ft_strlen(s2) + 1);
	else if (s1 != NULL && s2 != NULL)
	{
		ft_strlcpy (result, s1, ft_strlen(s1) + 1);
		ft_strlcat (result + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	}
	return (result);
}
