/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:22:10 by keaton            #+#    #+#             */
/*   Updated: 2022/07/16 20:22:11 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//функция определяет текущие активные ковычки
int	ft_quotes_identifier(char *str, int *quote_type)
{
	if (*str == '\'')
	{
		if (*quote_type == 0)
			*quote_type = 1;
		else if (*quote_type == 1)
			*quote_type = 0;
	}
	else if (*str == '"')
	{
		if (*quote_type == 0)
			*quote_type = 2;
		else if (*quote_type == 2)
			*quote_type = 0;
	}
	return (*quote_type);
}

//функция проверяет, корректно ли закрыты ковычки !!!!!!!!!!!!!!!!ГДЕ?!!!!!!!!!
int	ft_quotes_checker(char *str)
{
	int	quote_type;

	quote_type = 0;
	while (*str)
		quote_type = ft_quotes_identifier(str++, &quote_type);
	if (quote_type)
	{
		error_print(1, "hellshell: miss quote");
		return (0);
	}
	return (quote_type);
}

//функция печатает ошибку, ставит код и обнуляет переданный элемент чар-памяти,
// если он передан
char	**ft_out(char *err, int n_err, char **tab_to_nulfin)
{
	error_print(n_err, err);
	if (tab_to_nulfin)
		*tab_to_nulfin = NULL;
	return (NULL);
}

//функция занимается переносом последней команды в таблицу
char	**ft_fill_cmd_tab_line(char *str, char **cmds, char	**cmd_start)
{
	int		i;

	if (*(str - 1) == '|' || **cmd_start == '|')
		return (ft_out("minishell: syntax error near unexpected token `|\'\n",
				258, cmds));
	*cmds = (char *)malloc(sizeof(char) * (str - *cmd_start + 1));
	if (!*cmds)
		return (ft_out("minishell: malloc error\n", 1, NULL));
	(*cmds)[str - *cmd_start] = '\0';
	i = 0;
	while (*cmd_start != str)
		(*cmds)[i++] = *((*cmd_start)++);
	(*cmd_start)++;
	return (cmds);
}

//функция заполняет ноль-терминированный массив командами из стр
//выделяя под них память
char	**ft_fillcmds(char *str, char **cmds)
{
	int		quote_type;
	char	*cmd_start;

	quote_type = 0;
	cmd_start = str;
	quote_type = ft_quotes_identifier(str, &quote_type);
	while (*(str++))
	{
		quote_type = ft_quotes_identifier(str, &quote_type);
		if (!(*str) || (!quote_type && *str == '|'))
			if (!ft_fill_cmd_tab_line(str, cmds++, &cmd_start))
				return (NULL);
	}
	return (cmds);
}

