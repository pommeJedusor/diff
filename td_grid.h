#ifndef TD_GRID_H
# define TD_GRID_H

# include <stdio.h>
# include <stdlib.h>

typedef struct s_2d_grid
{
	int	**grid;
	int	width;
	int	height;
}	t_2d_grid;

t_2d_grid	make_2d_grid(int width, int height, int default_value);
t_2d_grid	*free_2d_grid(t_2d_grid *grid);
void		print_2d_grid(t_2d_grid *grid);

#endif
