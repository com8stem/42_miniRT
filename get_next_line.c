/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:00:15 by kishizu           #+#    #+#             */
/*   Updated: 2024/09/07 15:08:49 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static char	*x_ft_strjoin(char const *s1, char const *s2)
{
	int		total_len;
	char	*result;

	total_len = ft_strlen(s1) + ft_strlen(s2);
	if (total_len == 0)
		return (NULL);
	result = (char *)x_malloc(total_len + 1);
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

static char	*copy_to_note(int fd, char *note)
{
	char	*buf;
	int		read_bytes;
	char	*tmp;

	buf = (char *)x_malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buf == NULL)
		return (NULL);
	read_bytes = 1;
	while (read_bytes != 0)
	{
		if (ft_strchr(note, '\n') != NULL)
			break ;
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[read_bytes] = '\0';
		tmp = note;
		note = x_ft_strjoin(note, buf);
		free(tmp);
	}
	free(buf);
	return (note);
}

char	*get_next_line(int fd)
{
	static char	*note;
	char		*result;
	char		*tmp;
	size_t		result_len;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	note = copy_to_note(fd, note);
	if (note == NULL)
		return (NULL);
	if (ft_strchr(note, '\n') == NULL)
		result_len = ft_strlen(note);
	else
		result_len = ft_strchr(note, '\n') - note + 1;
	result = x_ft_substr(note, 0, result_len);
	tmp = note;
	note = x_ft_substr(note, result_len, ft_strlen(note) - result_len);
	free(tmp);
	return (result);
}
