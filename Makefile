# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nenvoy <nenvoy@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/26 15:50:13 by nenvoy            #+#    #+#              #
#    Updated: 2022/04/26 15:50:15 by nenvoy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER = minishell.h
#
SRC = main.c signal.c env_utils.c\
	  env.c pwd.c echo.c exit.c export.c unset.c
#
OBJ = $(SRC:.c=.o)
#
#FLAGS = -Wall -Werror -Wextra -I$(HEADER) -I//usr/local/Cellar/readline/8.1.2/include
FLAGS = -Wall -Werror -Wextra -I$(HEADER) -I/Users/$(USER)/.brew/Cellar/readline/8.1.2/include
#
NAME = minishell
#
.PHONY: all clean fclean re libft
#
all: libft $(NAME)
		@stty -ctlecho
#
$(NAME): $(OBJ) $(HEADER) Makefile
#	@$(CC) $(FLAGS) $(OBJ) -o $(NAME) -L//usr/local/Cellar/readline/8.1.2/lib/ -lreadline -L./libft -lft
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME) -L/Users/$(USER)/.brew/Cellar/readline/8.1.2/lib/ -lreadline -L./libft -lft
	@echo "\033[32m\033[1m[minishell compiled]"
#
%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@
#
libft :
	@make -C libft
#
clean:
	@make -C libft clean
	@$(RM) $(OBJ)
	@echo "\033[31m\033[1m[all clean]"
#
fclean: clean
	@$(RM) $(NAME)
	@$(RM) libft/libft.a
#
re: fclean all
#
