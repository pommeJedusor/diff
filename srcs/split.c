#include "diff.h"

int	get_lines_length(char **lines)
{
	int	i;

	i = 0;
	while (lines[i] != NULL)
		i++;
	return (i);
}

char	**free_lines(char **lines)
{
	int	i;

	i = 0;
	while (lines[i] != NULL)
	{
		free(lines[i]);
		i++;
	}
	free(lines);
	return (NULL);
}

char	**split(char *src, char c)
{
	int		nb_c;
	char	**lines;
	int		src_i;
	int		line_i;
	int		line_length;

	nb_c = count_char(src, c);
	lines = malloc(sizeof(char *) * (nb_c + 2));
	if (lines == NULL)
		return (NULL);
	src_i = 0;
	line_i = 0;
	while (line_i < nb_c + 1)
	{
		line_length = get_length_until_c(&src[src_i], c);
		lines[line_i] = ft_strndup(&src[src_i], line_length);
		if (lines[line_i] == NULL)
			return (free_lines(lines));
		line_i++;
		src_i += line_length + 1;
	}
	lines[line_i] = NULL;
	return (lines);
}
