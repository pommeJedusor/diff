#include "diff.h"

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		fprintf(stderr, "command requires 2 arguments\n");
		return (1);
	}
	compare_files(argv[1], argv[2]);
	return (0);
}
