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

void	initialise_2d_grid(t_2d_grid *grid, int default_value)
{
	int	x;
	int	y;

	y = 0;
	while (y < grid->height)
	{
		x = 0;
		while (x < grid->width)
		{
			grid->grid[y][x] = default_value;
			x++;
		}
		y++;
	}
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

void	print_2d_grid(t_2d_grid *grid)
{
	int		x;
	int		y;

	y = 0;
	while (y < grid->height)
	{
		x = 0;
		while (x < grid->width)
		{
			if (x != 0)
				printf(" ");
			printf("%d", grid->grid[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}
