#include "diff.h"

void	compare_lines_cell(t_2d_grid *td_grid, int x, int y, void *liness)
{
	char	**a;
	char	**b;
	int		**grid;

	a = ((char ***)liness)[0];
	b = ((char ***)liness)[1];
	grid = td_grid->grid;
	if (is_in_bounds(x, y + 1, td_grid))
		grid[y + 1][x] = min(grid[y + 1][x], grid[y][x] + 1);
	if (is_in_bounds(x + 1, y, td_grid))
		grid[y][x + 1] = min(grid[y][x + 1], grid[y][x] + 1);
	if (is_in_bounds(x + 1, y + 1, td_grid) && strcmp(a[x], b[y]) == 0)
		grid[y + 1][x + 1] = min(grid[y + 1][x + 1], grid[y][x]);
}

void	compare_lines(char **a, char **b, t_2d_grid *td_grid)
{
	char	**liness[2];

	td_grid->grid[0][0] = 0;
	liness[0] = a;
	liness[1] = b;
	apply_to_ever_cell(td_grid, &compare_lines_cell, (void *)liness);
}

void	fill_are_lines_same(t_2d_grid *grid, bool *are_lines_same[2])
{
	int	y;
	int	x;

	x = grid->width - 1;
	y = grid->height - 1;
	while (x != 0 || y != 0)
	{
		if (x > 0 && grid->grid[y][x - 1] == grid->grid[y][x] - 1)
		{
			are_lines_same[0][x - 1] = false;
			x--;
		}
		else if (y > 0 && grid->grid[y - 1][x] == grid->grid[y][x] - 1)
		{
			are_lines_same[1][y - 1] = false;
			y--;
		}
		else
		{
			are_lines_same[0][x - 1] = true;
			are_lines_same[1][y - 1] = true;
			x--;
			y--;
		}
	}
}

// returns 0 on success, -1 on failure
int	compare_line_allocate(t_2d_grid *grid, bool *are_lines_same[2],
	char **lines_a, char **lines_b)
{
	are_lines_same[0] = NULL;
	are_lines_same[1] = NULL;
	*grid = make_2d_grid(
			get_lines_length(lines_a) + 1,
			get_lines_length(lines_b) + 1,
			INT_MAX);
	if (grid->grid == NULL)
		return (-1);
	are_lines_same[0] = malloc(sizeof(bool) * grid->width);
	if (are_lines_same[0] == NULL)
	{
		free_2d_grid(grid);
		return (-1);
	}
	are_lines_same[1] = malloc(sizeof(bool) * grid->height);
	if (are_lines_same[1] == NULL)
	{
		free_2d_grid(grid);
		free(are_lines_same[0]);
		return (-1);
	}
	return (0);
}

// returns -1 if error, 0 otherwise
int	get_diff(char **lines_a, char **lines_b, bool *are_lines_same[2])
{
	t_2d_grid	grid;

	if (compare_line_allocate(&grid, are_lines_same, lines_a, lines_b) == -1)
		return (-1);
	compare_lines(lines_a, lines_b, &grid);
	fill_are_lines_same(&grid, are_lines_same);
	free_2d_grid(&grid);
	return (0);
}
