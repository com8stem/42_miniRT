/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:01:07 by kishizu           #+#    #+#             */
/*   Updated: 2024/09/07 15:10:45 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	**x_ft_split(const char *str, char c)
{
	char	**result;

	result = ft_split(str, c);
	if (result == NULL)
		config_error("ft_split failed");
	return (result);
}

char	*x_ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*result;

	result = ft_substr(s, start, len);
	if (result == NULL)
		config_error("ft_substr failed");
	return (result);
}

void	*x_ft_calloc(size_t count, size_t size)
{
	void	*result;

	result = ft_calloc(count, size);
	if (result == NULL)
		config_error("calloc failed");
	return (result);
}

void	*x_malloc(size_t size)
{
	void	*result;

	result = malloc(size);
	if (result == NULL)
		config_error("malloc failed");
	return (result);
}
