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
	char		**lines_a;
	char		**lines_b;
	bool		*are_lines_same[2];

	lines_a = split(a, '\n');
	if (lines_a == NULL)
		return ;
	lines_b = split(b, '\n');
	if (lines_b == NULL)
	{
		free_lines(lines_a);
		return ;
	}
	if (get_diff(lines_a, lines_b, are_lines_same) == -1)
	{
		free_lines(lines_a);
		free_lines(lines_b);
		return ;
	}
	print_diff(lines_a, lines_b, are_lines_same);
	free_lines(lines_a);
	free_lines(lines_b);
	free(are_lines_same[0]);
	free(are_lines_same[1]);
}

void	compare_files(char *file_name_a, char *file_name_b)
{
	char	*file_content_a;
	char	*file_content_b;

	file_content_a = get_file_content(file_name_a);
	file_content_b = get_file_content(file_name_b);
	if (file_content_a == NULL || file_content_b == NULL)
	{
		free(file_content_a);
		free(file_content_b);
		return ;
	}
	compare_strings(file_content_a, file_content_b);
	free(file_content_a);
	free(file_content_b);
}
