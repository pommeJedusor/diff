#ifndef COMPARE_LINES_H
# define COMPARE_LINES_H

# include <stdlib.h>
# include <string.h>
# include <limits.h>

# include "td_grid.h"
# include "math.h"
# include "split.h"

int	get_diff(char **lines_a, char **lines_b, bool *are_lines_same[2]);

#endif
