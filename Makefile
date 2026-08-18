PROGRAM_NAME = diff
CFLAGS = -Wall -Wextra -Werror -O3
CFILES = compare.c compare_lines.c math.c split.c ft_string.c td_grid.c td_grid_creation.c get_file_content.c main.c

all: ./$(PROGRAM_NAME)

./$(PROGRAM_NAME): $(CFILES)
	cc $(CFLAGS) -I ./ $(CFILES) -o $@

clean:

fclean: clean
	rm -f $(PROGRAM_NAME)

re: fclean all
