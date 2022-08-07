# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: keaton <keaton@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/26 15:50:13 by nenvoy            #+#    #+#              #
#    Updated: 2022/06/13 22:38:10 by keaton           ###   ########.fr        #
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
	executor/main.c
#
OBJ = $(SRC:.c=.o)
#Для дома
#FLAGS = -Wall -Werror -Wextra -I$(HEADER) -I//usr/local/Cellar/readline/8.1.2/include
# Для школы
# FLAGS = -Wall -Werror -Wextra -I$(HEADER) -I/Users/$(USER)/.brew/Cellar/readline/8.1.2/include
# Для отладки
FLAGS =   -I$(HEADER)



NAME = minishell
#
.PHONY: all clean fclean re libft
#
all: libft $(NAME)
		@stty -ctlecho
#
$(NAME): $(OBJ) $(HEADER) Makefile
#Для дома
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME) -L//usr/local/Cellar/readline/8.1.2/lib/ -lreadline -L./libft -lft
#Для школы
# 	@$(CC) $(FLAGS) $(OBJ) -o $(NAME) -L/Users/$(USER)/.brew/Cellar/readline/8.1.2/lib/ -lreadline -L./libft -lft
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
