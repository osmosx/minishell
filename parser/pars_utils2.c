#include "../minishell.h"

typedef struct	s_tkn
{
	int		type;
	char	*value;
	t_tkn	*next;
//	t_tkn	*prev;
}				t_tkn;

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

int	ft_tokens_checker(char *str)
{
	//функция проверяет, есть ли пайпы, перед которыми после предыдущего <,<<,>>,| только пробелы
	//та же ошибка если ничего перед & и ; после
	//короче нужно проверить, есть ли пустые токены после токенизации
	{
		printf("minishell: syntax error near unexpected token `|\'\n");
		g_error = 258;
		return (0);
	}
	return (0);
}

t_tkn	**ft_free_tkn(t_tkn **begin_tkn)
{
	t_tkn	active;
	t_tkn	prev;

	active = *begin_tkn
	prev = active;
	while (active->next)
	{
		if (active->value)
			free(active->value);
		active = active->next;
		free(prev);
		prev = active;
	}
	free(active);
	*begin_tkn = NULL;
	return (NULL);
}

t_tkn	**ft_tkn_add_back(t_tkn *new_tkn, t_tkn **begin_tkn)
{
	t_tkn	*last;

	if (!new_tkn)
		return (ft_free_tkn(begin_tkn));
	last = *begin_tkn
	while (current->next)
		last = current->next;
	last->next = new_tkn;
	return (begin_tkn)
}

int ft_def_token_type(char symb, int count)
{
	int type;

	if (count == 1)
	{
		if (symb == '|')
			type == 2;
		else if (symb == '<')
			type == 3;
		else if (symb == '>')
			type == 4;
		else if (symb == ' ')
			type == 7;
	}
	else if (count == 2)
	{
		if (symb == '<')
			type == 5;
		else if (symb == '>')
			type == 6;
	}
	else
		type = 0; //это заглушка
	return (type);
}

t_tkn	*ft_symb_tkn_init(char symb, int count)
{
	t_tkn	*new_tkn;

	new_tkn = (tkn *)malloc(sizeof(t_tkn));
	if (!new_tkn)
		return (NULL);
	new_tkn->type = ft_def_token_type(symb, count);
	new_tkn->value = NULL;
	new_tkn->next = NULL;
	return (new_tkn);
}

char	*ft_cmd_value_init(char **cmd)
{
	char	*cmd_value;
	char	*start;

	start = *cmd;
	while (!ft_is_symb_token(**cmd) && !ft_isspace(**cmd))
		(*cmd)++;
	cmd_value = (char *)malloc(sizeof(char) * (*cmd - start + 1));
	if (!cmd_value)
		return (NULL)
	ft_strlcpy(cmd_value, start, *cmd - start + 1);
	return (cmd_value);
}

t_tkn	*ft_cmd_tkn_init(char *cmd)
{
	t_tkn	*new_tkn;

	new_tkn = (tkn *)malloc(sizeof(t_tkn));
	if (!new_tkn)
		return (NULL);
	new_tkn->type = 1;
	new_tkn->value = ft_cmd_value_init(cmd);
	if (!new_tkn->value)
	{
		free(new_tkn);
		return (NULL);
	}
	new_tkn->next = NULL;
	return (new_tkn);
}

t_tkn	**ft_tkn(char **cmd, t_tkn **tkn_begin, char symb, int maxlen)
{
	int		count;

	count = 0;
	while (**cmd == symb && count < maxlen)
	{
		count++;
		(*cmd)++;
	}
	if (count > 0)
		tkn_begin = ft_tkn_add_back(ft_symb_tkn_init(symb, count), tkn_begin);
	return (tkn_begin);
}

int	ft_is_symb_token(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

t_tkn	**ft_command_tokenizer(char *cmd, t_tkn **tkn_begin)
{

	char	arr;
	int		count;

	while (*cmd && tkn_begin)
	{
		if (ft_isspace(*cmd))
		{
			if (!ft_tkn_add_back(ft_symb_tkn_init(' ', 1), tkn_begin))//что если между " " или $SPACE
				return (NULL);
			while (ft_isspace(*cmd))
				cmd++;
		}
		if (!ft_tkn(&cmd, tkn_begin, '>', 2) ||
			!ft_tkn(&cmd, tkn_begin, '<', 2))
			return (NULL);
		if (!ft_is_symb_token(*cmd) && !ft_isspace(*cmd))
			tkn_begin = ft_tkn_add_back(ft_cmd_tkn_init(&cmd), tkn_begin);
	}
	//функция создаёт токены из существующей строчной команды
	if (!tkn_begin)
		g_error = -1;
	return (tkn_begin)
	//???и возвращает код ошибки (-1 на малок и 1 если есть ошибка в коде токена например)???
}
// должна быть функция, которая пропускает пробелы и собирает стрелки в токены.
//в остальные токены собирается всё, что разделено пробелами или <> (|?, ||, &&)
//все токены добавляются в лист токенов

//далее функция, которая типизирует имеющийся список токенов по составу
//всё, что не нашло тип или билтин, становится типом "аргумент"

//далее функция, которая проверяет на пустые типы и выдаёт нужную нам ошибку

//дальше если у токена есть содержимое, мы его модифицируем по $

tkn_begin = ft_tkn_add_back(ft_symb_tkn_init('0', 0), tkn_begin);//инициализация первого псевдотокена. не забыть удалить
tkn_begin = ft_tkn_add_back(ft_symb_tkn_init('|', 1), tkn_begin);//токен между пайпами
