/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:59:11 by kishizu           #+#    #+#             */
/*   Updated: 2023/11/17 17:55:04 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	total_len;

	if (dst == NULL && dstsize == 0)
		return (ft_strlen(src) + dstsize);
	dest_len = ft_strlen((const char *)dst);
	src_len = ft_strlen(src);
	total_len = dest_len + src_len;
	if (dstsize <= dest_len)
		return (src_len + dstsize);
	ft_strlcpy(dst + ft_strlen(dst), src, total_len + 1);
	return (total_len);
}
