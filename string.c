#include "diff.h"

int	count_char(char *src, char c)
{
	int	counter;
	int	i;

	counter = 0;
	i = 0;
	while (src[i] != '\0')
	{
		if (src[i] == c)
			counter++;
		i++;
	}
	return (counter);
}

char	*ft_strndup(char *src, int length)
{
	char	*dest;
	int		i;

	dest = malloc(sizeof(char) * (length + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	get_length_until_c(char *src, char c)
{
	int	i;

	i = 0;
	while (src[i] != '\0' && src[i] != c)
		i++;
	return (i);
}
