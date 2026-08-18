#ifndef COMPARE_H
# define COMPARE_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <ft_string.h>

# include "td_grid.h"
# include "split.h"
# include "math.h"
# include "compare_lines.h"
# include "get_file_content.h"

void	compare_strings(char *a, char *b);
void	compare_files(char *file_name_a, char *file_name_b);

#endif
