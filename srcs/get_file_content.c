#include "diff.h"

char	*get_file_content(char *file_name)
{
	int		fd;
	int		nb_bytes_read;
	int		total_bytes_read;
	char	*file_content;

	nb_bytes_read = 1;
	total_bytes_read = 0;
	file_content = realloc(NULL, total_bytes_read + 1024);
	fd = open(file_name, O_RDONLY);
	while (nb_bytes_read != 0 && file_content != NULL)
	{
		nb_bytes_read = read(fd, &file_content[total_bytes_read], 1024);
		total_bytes_read += nb_bytes_read;
		file_content = realloc(file_content, total_bytes_read + 1024);
	}
	close(fd);
	return (file_content);
}
