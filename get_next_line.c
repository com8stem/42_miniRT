#include "minirt.h"

static char	*copy_to_note(int fd, char *note)
{
	char	*buf;
	int		read_bytes;
	char	*tmp;

	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
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
		note = ft_strjoin(note, buf);
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
	result = ft_substr(note, 0, result_len);
	tmp = note;
	note = ft_substr(note, result_len, ft_strlen(note) - result_len);
	free(tmp);
	return (result);
}