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

char	**ft_fillcmds(char *str, char **cmds)
{
	//функция заполняет ноль-терминированный массив командами из стр
	//выделяя под них память
	int		quote_type;
	char	*cmd_start;
	int		i;

	quote_type = 0;
	cmd_start = str;
	quote_type = ft_quotes_identifier(str, &quote_type);
	while (*(str++))
	{
		quote_type = ft_quotes_identifier(str, &quote_type);
		if (!(*str) || (!quote_type && *str == '|'))
		{
			if (*(str - 1) == '|' || *cmd_start == '|')
			{
				//здесь можно сделать умнее, если оставить это токенами
				printf("minishell: syntax error near unexpected token `|\'\n");
				g_error = 258;
				return (0);
			}
			*cmds = (char *)malloc(sizeof(char) * (str - cmd_start + 1));
			(*cmds)[str - cmd_start] = '\0';
			i = 0;
			while (cmd_start != str)
				(*cmds)[i++] = *(cmd_start++);
			//эти 4 строки часть можно заменить на стрндуп
			cmds++;
			cmd_start++;
		}
		/*if (i == 0)
		{
			write(2, "minishell: syntax error near unexpected token `|\'\n", 50);
			exit (258);
		}   ---если сверху делать токенизацию и готовить под или(||)*/
	}
	return (cmds);//наверное цмдс -1

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

char	**ft_pipe_separator(char *str)
{
	//нам не нужно разделять команды по тчкзпт
	//функция разделяет команды по |
	//и если есть пустые, то выходит с ошьбкой около '|'
	char	**cmds;
	int		n_of_cmds;

	n_of_cmds = ft_count_tokens(str, '|') + 1;
	cmds = (char **)malloc(sizeof(char *) * (n_of_cmds + 1));
	cmds[n_of_cmds] = NULL;
	ft_fillcmds(str, cmds);
	return (cmds);
	//вероятно логичнее создать лист команд, на котором помимо самой команды будет храниться лист токенов команды
}

int	ft_command_tokenizer(t_cmd *cmd, t_tkn **tkn_begin)
{
	//функция создаёт токены из существующей строчной команды
	//и возвращает код ошибки (-1 на малок и 1 если есть ошибка в коде токена например)
}
// должна быть функция, которая пропускает пробелы и собирает стрелки в токены.
//в остальные токены собирается всё, что разделено пробелами или <> (|?, ||, &&)
//все токены добавляются в лист токенов

//далее функция, которая типизирует имеющийся список токенов по составу
//всё, что не нашло тип или билтин, становится типом "аргумент"

//далее функция, которая проверяет на пустые типы и выдаёт нужную нам ошибку

//дальше если у токена есть содержимое, мы его модифицируем по $

