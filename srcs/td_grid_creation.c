#include "diff.h"

t_2d_grid	*free_2d_grid(t_2d_grid *grid)
{
	int	i;

	i = 0;
	while (i < grid->height && grid->grid[i] != NULL)
	{
		free(grid->grid[i]);
		i++;
	}
	free(grid->grid);
	grid->grid = NULL;
	return (grid);
}

void	initialise_cell(t_2d_grid *grid, int x, int y, void *default_value)
{
	grid->grid[y][x] = *(int *)default_value;
}

void	initialise_2d_grid(t_2d_grid *grid, int default_value)
{
	apply_to_ever_cell(grid, &initialise_cell, (void *)&default_value);
}

t_2d_grid	make_2d_grid(int width, int height, int default_value)
{
	t_2d_grid	grid;
	int			i;

	grid.width = width;
	grid.height = height;
	grid.grid = malloc(sizeof(int *) * height);
	if (grid.grid == NULL)
		return (grid);
	i = 0;
	while (i < height)
	{
		grid.grid[i] = malloc(sizeof(int) * width);
		if (grid.grid[i] == NULL)
			return (*free_2d_grid(&grid));
		i++;
	}
	initialise_2d_grid(&grid, default_value);
	return (grid);
}
