HEADER = minishell.h
#
SRC = main.c
#
OBJ = $(SRC:.c=.o)
#
FLAGS = -Wall -Werror -Wextra -I$(HEADER) -I/Users/$(USER)/.brew/Cellar/readline/8.1.2/include
#
NAME = minishell
#
all: $(NAME)
	@stty -ctlecho
#
$(NAME): $(OBJ) $(HEADER) Makefile
	@$(CC) -L/Users/$(USER)/.brew/Cellar/readline/8.1.2/lib/ -lreadline  $(FLAGS) $(OBJ) -o $@
	@echo "\033[32m\033[1m[minishell compiled]"
#
%.o: %.c
	@$(CC) $(FLAGS) -c $<
#
clean:
	@rm -rf $(OBJ)
	@echo "\033[31m\033[1m[all clean]"
#
fclean: clean
	@rm -rf $(NAME)
#
re: fclean all
#