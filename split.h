#ifndef SPLIT_H

# define SPLIT_H

# include <stdlib.h>

# include "string.h"

char	**split(char *src, char c);
char	**free_lines(char **lines);
int		get_lines_length(char **lines);

#endif
