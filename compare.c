#include "diff.h"

int	get_lines_length(char **lines)
{
	int	i;

	i = 0;
	while (lines[i] != NULL)
		i++;
	return (i);
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	is_in_bounds(int x, int y, t_2d_grid *grid)
{
	return (x > 0 && x < grid->width && y > 0 && y < grid->height);
}

void	compare_lines(char **a, char **b, t_2d_grid *td_grid)
{
	int	y;
	int	x;
	int	**grid;

	td_grid->grid[0][0] = 0;
	grid = td_grid->grid;
	y = 0;
	while (y < td_grid->height)
	{
		x = 0;
		while (x < td_grid->width)
		{
			if (y + 1 != td_grid->height)
				grid[y + 1][x] = min(grid[y + 1][x], grid[y][x] + 1);
			if (x + 1 != td_grid->width)
				grid[y][x + 1] = min(grid[y][x + 1], grid[y][x] + 1);
			if (is_in_bounds(x + 1, y + 1, td_grid) && strcmp(a[x], b[y]) == 0)
				grid[y + 1][x + 1] = min(grid[y + 1][x + 1], grid[y][x]);
			else if (is_in_bounds(x + 1, y + 1, td_grid))
				grid[y + 1][x + 1] = min(grid[y + 1][x + 1], grid[y][x] + 1);
			x++;
		}
		y++;
	}
}

void	free_compare_datas(char **lines_a, char **lines_b, t_2d_grid *grid, bool *are_lines_same[2])
{
	free_lines(lines_a);
	free_lines(lines_b);
	free_2d_grid(grid);
	free(are_lines_same[0]);
	free(are_lines_same[1]);
}

void	fill_are_lines_same(t_2d_grid *grid, bool *are_lines_same[2])
{
	int	y;
	int	x;
	int	move_values[3];

	x = grid->width - 1;
	y = grid->height - 1;
	while (x != 0 || y != 0)
	{
		move_values[0] = INT_MAX;
		move_values[1] = INT_MAX;
		move_values[2] = INT_MAX;
		if (x > 0 && grid->grid[y][x - 1] == grid->grid[y][x] - 1)
			move_values[0] = grid->grid[y][x - 1];
		if (y > 0 && grid->grid[y - 1][x] == grid->grid[y][x] - 1)
			move_values[1] = grid->grid[y - 1][x];
		if (y > 0 && x > 0 && grid->grid[y - 1][x - 1] == grid->grid[y][x])
			move_values[2] = grid->grid[y - 1][x - 1];
		if (move_values[0] <= move_values[1] && move_values[0] <= move_values[2])
		{
			are_lines_same[0][x - 1] = false;
			x--;
		}
		else if (move_values[1] <= move_values[2])
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

void	print_are_lines_same(t_2d_grid *grid, bool *are_lines_same[2])
{
	int	i;

	i = 0;
	while (i < grid->width - 1)
	{
		if (i != 0)
			printf(" ");
		printf("%b", are_lines_same[0][i]);
		i++;
	}
	printf("\n");
	i = 0;
	while (i < grid->height - 1)
	{
		if (i != 0)
			printf(" ");
		printf("%b", are_lines_same[1][i]);
		i++;
	}
	printf("\n");
}

void	print_diff(char **lines_a, char **lines_b, bool *are_lines_same[2])
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (lines_a[x] != NULL || lines_b[y] != NULL)
	{
		while (lines_a[x] != NULL && !are_lines_same[0][x])
		{
			printf("<%s\n", lines_a[x]);
			x++;
		}
		while (lines_b[y] != NULL && !are_lines_same[1][y])
		{
			printf(">%s\n", lines_b[y]);
			y++;
		}
		while (lines_a[x] != NULL && lines_b[y] != NULL && are_lines_same[0][x] && are_lines_same[1][y])
		{
			printf(" %s\n", lines_b[y]);
			x++;
			y++;
		}
	}
}

void	compare_strings(char *a, char *b)
{
	char		**a_lines;
	char		**b_lines;
	bool		*are_lines_same[2];
	t_2d_grid	grid;

	a_lines = split(a, '\n');
	b_lines = split(b, '\n');
	grid = make_2d_grid(
			get_lines_length(a_lines) + 1,
			get_lines_length(b_lines) + 1,
			INT_MAX);
	are_lines_same[0] = malloc(sizeof(bool) * grid.width);
	are_lines_same[1] = malloc(sizeof(bool) * grid.height);
	if (a_lines == NULL || b_lines == NULL || grid.grid == NULL
			|| are_lines_same[0] == NULL || are_lines_same[1] == NULL)
	{
		free_compare_datas(a_lines, b_lines, &grid, are_lines_same);
		return ;
	}
	compare_lines(a_lines, b_lines, &grid);
	fill_are_lines_same(&grid, are_lines_same);
	//printf("grid:\n");
	//print_2d_grid(&grid);
	//printf("are_lines_same:\n");
	//print_are_lines_same(&grid, are_lines_same);
	printf("<-- input 1 -->\n%s\n", a);
	printf("<-- end input 1 -->\n");
	printf("<-- input 2 -->\n%s\n", b);
	printf("<-- end input 2 -->\n");
	printf("<-- output -->\n");
	print_diff(a_lines, b_lines, are_lines_same);
	printf("<-- end output -->\n");
	free_compare_datas(a_lines, b_lines, &grid, are_lines_same);
}
