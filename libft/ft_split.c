/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:38:43 by kishizu           #+#    #+#             */
/*   Updated: 2023/10/11 21:29:09 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(const char *str, char charset)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	if (str == NULL)
		return (0);
	while (*str)
	{
		if (*str == charset)
		{
			in_word = 0;
		}
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		str++;
	}
	return (count);
}

char	*ft_strncpy(char *dest, const char *src, unsigned int n)
{
	char	*dest_origin;

	dest_origin = dest;
	while (n > 0 && *src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
		n--;
	}
	while (n > 0)
	{
		*dest = '\0';
		dest++;
		n--;
	}
	return (dest_origin);
}

void	*freestr(char **result, int index)
{
	while (index >= 0)
	{
		free(result[index]);
		index--;
	}
	free (result);
	return (NULL);
}

char	*copy_word(const char *s, char c)
{
	int		length;
	char	*tmp;

	length = 0;
	while (s[length] && s[length] != c)
		length++;
	tmp = (char *)malloc((length + 1) * sizeof(char));
	if (tmp == NULL)
	{
		return (NULL);
	}
	ft_strncpy(tmp, s, length);
	tmp[length] = '\0';
	return (tmp);
}

char	**ft_split(char const *s, char c)
{
	int		index;
	char	**result;
	char	*tmp;

	index = 0;
	if (s == NULL)
		return (NULL);
	result = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	while (*s != '\0')
	{
		if (*s != c)
		{
			tmp = copy_word(s, c);
			if (tmp == NULL)
				return (freestr(result, index - 1));
			result[index++] = tmp;
			s = s + ft_strlen(tmp) - 1;
		}
		s++;
	}
	result[index] = NULL;
	return (result);
}
