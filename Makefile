# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: keaton <keaton@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/26 15:50:13 by nenvoy            #+#    #+#              #
#    Updated: 2022/08/15 01:02:33 by keaton           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER = minishell.h
#
SRC = main.c \
	builtin/env.c builtin/pwd.c builtin/echo.c builtin/exit.c builtin/export.c builtin/unset.c builtin/cd.c \
	builtin/signal.c builtin/utils.c builtin/export_utils.c builtin/env_utils.c \
	parser/parser.c parser/cmd_creator.c parser/cmd_tab_creator.c parser/file_creator.c parser/quotes_utils.c \
	parser/quotes.c parser/tkn_creators.c parser/tkn_utils.c parser/file_creator_two.c parser/parser_two.c \
	parser/tkn_utils_two.c parser/quotes_two.c \
	executor/exec.c executor/heredoc.c executor/exec_utils.c executor/exec_utils_two.c executor/exec_utils_three.c \
	parser_test.c
#
OBJ = $(SRC:.c=.o)
#Для дома
#FLAGS = -Wall -Werror -Wextra -I$(HEADER) -I//usr/local/Cellar/readline/8.1.2/include
# Для школы
# FLAGS = -Wall -Werror -Wextra -I$(HEADER) -I/Users/$(USER)/.brew/Cellar/readline/8.1.2/include
# Для отладки
FLAGS =   -I $(HEADER)

NAME = minishell
#
.PHONY: all clean fclean re libft
#
all: libft $(NAME)
		@stty -ctlecho
#
$(NAME): $(OBJ) $(HEADER) Makefile
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME) -lreadline -L./libft -lft
	@echo "\033[32m\033[1m[minishell compiled]"
#Для дома
#	@$(CC) $(FLAGS) $(OBJ) -o $(NAME) -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include  -L./libft -lft
#Для школы
#
#Для Linux
#	@$(CC) $(FLAGS) $(OBJ) -o $(NAME) -lreadline -L/home/linuxbrew/.linuxbrew/Cellar/readline/8.1.2/lib -I/home/linuxbrew/.linuxbrew/Cellar/readline/8.1.2/include -L./libft -lft

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
