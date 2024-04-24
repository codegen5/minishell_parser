CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = minishell
SRC = main.c ./parser/lexer.c ./parser/parser1.c ./parser/parser2.c ./parser/parse_pushback.c \
	./parser/split_token1.c ./parser/split_token2.c ./parser/split_token3.c
OBJ = $(SRC:.c=.o)
LIBFT = libft/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT) -lreadline -fsanitize=address -g

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re