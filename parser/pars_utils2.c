typedef struct	s_tkn
{
	int		type;
	char	*value;
	t_tkn	*next;
	t_tkn	*prev;
}				t_tkn;

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

void	ft_free_tkn(t_tkn	*tkn)
{
	if (tkn->value)
		free(tkn->value);
	free(tkn);
}

t_tkn	**ft_free_tkn_list(t_tkn **begin_tkn)
{
	//проверяет, передали ли начало и если да, то фришит строки и токены
	t_tkn	*active;
	t_tkn	*prev;

	if (!*begin_tkn)
		return (NULL);
	active = *begin_tkn;
	prev = active;
	while (active->next)
	{
		active = active->next;
		ft_free_tkn(prev);
		prev = active;
	}
	ft_free_tkn(active);
	*begin_tkn = NULL;
	return (NULL);
}

t_tkn	**ft_tkn_add_back(t_tkn *new_tkn, t_tkn **begin_tkn)
{
	//проверяет, передали ли новый и если начало не 0, добавляет его в конец, а если 0 - возвращает новый как начало
	t_tkn	*last;

	if (!new_tkn)
		return (ft_free_tkn_list(begin_tkn));
	last = *begin_tkn;
	if (!last)
	{
		begin_tkn = &new_tkn;
		return (begin_tkn);
	}
	while (last->next)
		last = last->next;
	last->next = new_tkn;
	return (begin_tkn);
}

/*
заглушка - 0
текст - 1
пайп - 2
< - 3
> - 4
<< - 5
>> - 6
пробел - 7
*/

int ft_def_token_type(char symb, int count)
{
	//определяет тип полученного символа для присвоения индекса токену
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
	//инициализирует токен символа, заполняя нужные значения и возвращает его адрес
	t_tkn	*new_tkn;

	new_tkn = (t_tkn *)malloc(sizeof(t_tkn));
	if (!new_tkn)
		return (NULL);
	new_tkn->type = ft_def_token_type(symb, count);
	new_tkn->value = NULL;
	new_tkn->next = NULL;
	new_tkn->prev = NULL;
	return (new_tkn);
}

char	*ft_cmd_value_init(char **cmd)
{
	//заполняет значение токена текста и возвращает его адрес.
	//Также двигает строку до конца строки, токена символа или пробела c учетом ковычек
	char	*cmd_value;
	char	*start;
	int		quote_type;

	quote_type = 0;
	start = *cmd;
	while (!quote_type && !ft_is_symb_token(**cmd) && !ft_isspace(**cmd) && **cmd)
		quote_type = ft_quotes_identifier((*cmd)++, &quote_type);
	cmd_value = (char *)malloc(sizeof(char) * (*cmd - start + 1));
	if (!cmd_value)
		return (NULL);
	ft_strlcpy(cmd_value, start, *cmd - start + 1);
	return (cmd_value);
}

t_tkn	*ft_cmd_tkn_init(char **cmd)
{
	//инициализирует токен текста, заполняя нужные значения и возвращает его адрес.
	//Также двигает строку до конца строки, токена символа или пробела
	t_tkn	*new_tkn;

	new_tkn = (t_tkn *)malloc(sizeof(t_tkn));
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
	//проверяет, являются ли символы строки токеном symb и если да, создаёт соответствующий токен и двигает строку
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
	//идёт по строке cmd и токенизирует пробелы, стрелки и строки пока не закончится строка
	while (*cmd && *tkn_begin)
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
		if (!ft_is_symb_token(*cmd) && !ft_isspace(*cmd))
			if (!ft_tkn_add_back(ft_cmd_tkn_init(&cmd), tkn_begin))
				return (NULL);
	}
	return (tkn_begin);
	//???и возвращает код ошибки (-1 на малок и 1 если есть ошибка в коде токена например)???
}
// должна быть функция, которая пропускает пробелы и собирает стрелки в токены.
//в остальные токены собирается всё, что разделено пробелами или <> (|?, ||, &&)
//все токены добавляются в лист токенов

//далее функция, которая типизирует имеющийся список токенов по составу
//всё, что не нашло тип или билтин, становится типом "аргумент"

//далее функция, которая проверяет на пустые типы и выдаёт нужную нам ошибку

//дальше если у токена есть содержимое, мы его модифицируем по $

// main
// {
// 	t_tkn	*tkn_begin;

// 	g_error = 0
// 	if (!ft_tkn_add_back(ft_symb_tkn_init('0', 0), &tkn_begin)
// 	|| !ft_line_tokenizer(char *cmd, &tkn_begin, , char **env))//инициализация первого псевдотокена. не забыть удалить
// 		if (!g_error)
// 		{
// 			g_error = -1;
// 			printf("Malloc didn't give memory. Try again\n");
// 			return (???);
// 		}
// }
