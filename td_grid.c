#include "diff.h"

void	apply_to_ever_cell(t_2d_grid *grid,
		void (*f)(t_2d_grid *, int, int, void *), void *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < grid->height)
	{
		x = 0;
		while (x < grid->width)
		{
			f(grid, x, y, data);
			x++;
		}
		y++;
	}
}

void	print_2d_cell(t_2d_grid *grid, int x, int y, void *_)
{
	(void)_;
	if (x != 0)
		printf(" ");
	printf("%d", grid->grid[y][x]);
	if (x + 1 == grid->width)
		printf("\n");
}

void	print_2d_grid(t_2d_grid *grid)
{
	apply_to_ever_cell(grid, &print_2d_cell, NULL);
}

int	is_in_bounds(int x, int y, t_2d_grid *grid)
{
	return (x >= 0 && x < grid->width && y >= 0 && y < grid->height);
}
