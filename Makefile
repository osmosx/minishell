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
	executor/exec.c executor/heredoc.c executor/exec_utils.c executor/exec_utils_two.c executor/exec_utils_three.c

#
OBJ = $(SRC:.c=.o)

FLAGS =  -Wall -Wextra -Werror -I .

NAME = minishell
#
.PHONY: all clean fclean re libft
#
all: libft $(NAME)
		@stty -ctlecho
#
$(NAME): $(OBJ) $(HEADER) Makefile
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME) -lreadline -L./readline/8.1.2/lib -I./readline/8.1.2/include -L./libft -lft
	@echo "\033[32m\033[1m[minishell compiled]"

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@
#
libft :
	@make -s -C libft
#
clean:
	@make -s -C libft clean
	@$(RM) $(OBJ)
	@echo "\033[31m\033[1m[all clean]"
#
fclean: clean
	@$(RM) $(NAME)
	@$(RM) libft/libft.a
#
re: fclean all
#
