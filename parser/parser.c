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

int	ft_quotes_identifier(char *str, int *quote_type)
{
	//функция определяет текущие активные ковычки
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

int	ft_quotes_checker(char *str)
{
	//функция проверяет, корректно ли закрыты ковычки
	int quote_type;

	quote_type = 0;
	while (*str)
		quote_type = ft_quotes_identifier(str++, &quote_type);
	if (quote_type)
	{
		return (write(2, "minishell: miss quote\n", 22));
		exit(1);
	}
	return(quote_type);
}

char	**ft_out(char *err, int n_err, char **tab_to_nulfin)
{
	//функция печатает ошибку, ставит код и обнуляет переданный элемент чар-памяти, если он передан
	printf("%s", err);
	g_error = n_err;
	if (tab_to_nulfin)
		*tab_to_nulfin = NULL;
	return (NULL);
}

char	**ft_fill_cmd_tab_line(char *str, char **cmds, char	**cmd_start)
{
	//функция занимается переносом последней команды в таблицу
	int		i;

	if (*(str - 1) == '|' || **cmd_start == '|')//Если предыдущий символ или символ начала команды - пайп->два пайпа подряд
		return (ft_out("minishell: syntax error near unexpected token `|\'\n", 258, cmds));
	*cmds = (char *)malloc(sizeof(char) * (str - *cmd_start + 1));
	if(!cmds)
		return (ft_out("minishell: malloc error\n", 1, NULL));
	(*cmds)[str - *cmd_start] = '\0';
	i = 0;
	while (*cmd_start != str)
		(*cmds)[i++] = *((*cmd_start)++);
	(*cmd_start)++;
	return (cmds);
}

char	**ft_fillcmds(char *str, char **cmds)
{
	//функция заполняет ноль-терминированный массив командами из стр
	//выделяя под них память
	int		quote_type;
	char	*cmd_start;

	quote_type = 0;
	cmd_start = str;
	quote_type = ft_quotes_identifier(str, &quote_type);
	while (*(str++))
	{
		quote_type = ft_quotes_identifier(str, &quote_type);
		if (!(*str) || (!quote_type && *str == '|'))//Если мы дошли до конца строки или следующего пайпа
			if (!ft_fill_cmd_tab_line(str, cmds++, &cmd_start))
				return(NULL);
	}
	return (cmds);
}

int	ft_count_tokens(char *str, char symb)
{
	//считает количество символов в строке с пропуском всех ковычек
	//для того, чтобы создать нужное количество токенов потом
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
	//вероятно логичнее создать лист команд, на котором помимо самой команды будет храниться лист токенов команды
}

//идёт по строке cmd и токенизирует пробелы, стрелки и строки пока не закончится строка
t_tkn	**ft_command_tokenizer(char *cmd, t_tkn **tkn_begin)
{
	while (*cmd)// && *tkn_begin)
	{
		if (ft_isspace(*cmd))
		{
			if (!ft_tkn_add_back(ft_symb_tkn_init(' ', 1), tkn_begin))
				return (NULL);
			while (ft_isspace(*cmd))
				cmd++;
		}
		if (!ft_tkn(&cmd, tkn_begin, '>', 2) ||
			!ft_tkn(&cmd, tkn_begin, '<', 2))
			return (NULL);
		if (!ft_is_symb_token(*cmd) && !ft_isspace(*cmd) && *cmd)
			if (!ft_tkn_add_back(ft_cmd_tkn_init(&cmd), tkn_begin))
				return (NULL);
	}
	return (tkn_begin);
}

char	**ft_line_tokenizer(char *str, t_cmd **cmd_begin, char **env)
{
	//перед вызовом этой функции проверить, что строка не пустая
	//функция создаёт токены команд в список из существующего строчного инпута
	//сначала разбивает по пайпам, а потом обрабатывает каждую область отдельно
	t_tkn	*tkn_begin;
//	t_tkn	*tkn_blanc;
	char	**cmds;
	char	**first_cmd;

	cmds = ft_pipe_separator(str);
	first_cmd = cmds;
	tkn_begin = NULL;
//	ft_printtab(cmds);
	while (*cmds)
	{
		if (!ft_tkn_add_back(ft_symb_tkn_init('0', 0), &tkn_begin)
			|| !ft_command_tokenizer(*(cmds++), &tkn_begin))//инициализация первого псевдотокена. не забыть удалить
			return (ft_free(first_cmd));
//		tkn_blanc = tkn_begin;
//		tkn_begin = tkn_begin->next;
		ft_tkn_del(tkn_begin, &tkn_begin);//удаление псевдотокена
		// write(1, "tkn\n",4);
		// ft_print_tkn(tkn_begin);
		if(!ft_cmd_add_back(ft_cmd_filler(&tkn_begin, env), cmd_begin))
			return (NULL);
		// write(1, "tkn:\n", 5);
		// ft_print_tkn(tkn_begin);
		ft_free_tkn_list(&tkn_begin);//освобождение листа токенов
	// write(1, *cmds, 6);
	}
//	ft_free(first_cmd);
	return (first_cmd);
}
// *предполагаем, что ошибка двух последовательных токенов пайпа уже проверена

//3 - получаем список t_cmd   если звёздочка не раскрыта, то тут можно проверить на абсолютно пустой цмд

//4 - исполняем пайп
//4.1 - реализуем перенаправления
