#include "diff.h"

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
		while (lines_a[x] != NULL && lines_b[y] != NULL
			&& are_lines_same[0][x] && are_lines_same[1][y])
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

	a_lines = split(a, '\n');
	if (a_lines == NULL)
		return ;
	b_lines = split(b, '\n');
	if (b_lines == NULL)
	{
		free_lines(a_lines);
		return ;
	}
	if (get_diff(a_lines, b_lines, are_lines_same) == -1)
	{
		free_lines(a_lines);
		free_lines(b_lines);
		return ;
	}
	printf("<-- input 1 -->\n%s\n<-- end input 1 -->\n", a);
	printf("<-- input 2 -->\n%s\n<-- end input 2 -->\n<-- output -->\n", b);
	print_diff(a_lines, b_lines, are_lines_same);
	printf("<-- end output -->\n");
	free_lines(a_lines);
	free_lines(b_lines);
}
