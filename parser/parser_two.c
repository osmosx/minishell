/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:22:10 by keaton            #+#    #+#             */
/*   Updated: 2022/07/16 20:22:11 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//считает количество символов в строке с пропуском всех ковычек
//для того, чтобы создать нужное количество токенов потом
int	ft_count_tokens(char *str, char symb)
{
	int	quote_type;
	int	counter;

	counter = 0;
	quote_type = 0;
	while (*str)
	{
		quote_type = ft_quotes_identifier(str, &quote_type);
		if (!quote_type && *str == symb)
			counter += 1;
		str++;
	}
	return (counter);
}

//нам не нужно разделять команды по тчкзпт
//функция разделяет команды по |
//и если есть пустые, то выходит с ошьбкой около '|'
char	**ft_pipe_separator(char *str)
{
	char	**cmds;
	int		n_of_cmds;

	n_of_cmds = ft_count_tokens(str, '|') + 1;
	cmds = (char **)malloc(sizeof(char *) * (n_of_cmds + 1));
	cmds[n_of_cmds] = NULL;
	ft_fillcmds(str, cmds);
	return (cmds);
}

//идёт по строке cmd и токенизирует пробелы, стрелки и строки пока
// не закончится строка
t_tkn	**ft_command_tokenizer(char *cmd, t_tkn **tkn_begin)
{
	while (*cmd)
	{
		if (ft_isspace(*cmd))
		{
			if (!ft_tkn_add_back(ft_symb_tkn_init(' ', 1), tkn_begin))
				return (NULL);
			while (ft_isspace(*cmd))
				cmd++;
		}
		if (!ft_tkn(&cmd, tkn_begin, '>', 2)
			|| !ft_tkn(&cmd, tkn_begin, '<', 2))
			return (NULL);
		if (!ft_is_symb_token(*cmd) && !ft_isspace(*cmd) && *cmd)
			if (!ft_tkn_add_back(ft_cmd_tkn_init(&cmd), tkn_begin))
				return (NULL);
	}
	return (tkn_begin);
}

//перед вызовом этой функции проверить, что строка не пустая
//функция создаёт токены команд в список из существующего строчного инпута
//сначала разбивает по пайпам, а потом обрабатывает каждую область отдельно
char	**ft_line_tokenizer(char *str, t_cmd **cmd_begin, char **env)
{
	t_tkn	*tkn_begin;
	char	**cmds;
	char	**first_cmd;

	cmds = ft_pipe_separator(str);
	first_cmd = cmds;
	tkn_begin = NULL;
	while (*cmds)
	{
		if (!ft_tkn_add_back(ft_symb_tkn_init('0', 0), &tkn_begin)
			|| !ft_command_tokenizer(*(cmds++), &tkn_begin))
			return (ft_free(first_cmd));
		ft_tkn_del(tkn_begin, &tkn_begin);
		if (!ft_cmd_add_back(ft_cmd_filler(&tkn_begin, env), cmd_begin))
			return (NULL);
		ft_free_tkn_list(&tkn_begin);
	}
	return (first_cmd);
}

