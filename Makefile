NAME = pipex
LIBFT_DIR = libft
PRINTF_DIR = libftprintf
LIBS = -L$(LIBFT_DIR) -lft -L$(PRINTF_DIR) -lftprintf
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
SRC =	main.c \
		error.c \
		filepath.c \
		input_process.c \
		output_process.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBFT_DIR)
	make -C $(PRINTF_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(PRINTF_DIR)
	$(RM) $(OBJ)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(PRINTF_DIR)
	$(RM) $(NAME) $(OBJ)

re: fclean all

.PHONY: all clean fclean re