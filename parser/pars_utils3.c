#include "../minishell.h"

//redirect implementation
typedef struct	s_tkn
{
	int		type;
	char	*value;
	t_tkn	*next;
	t_tkn	*prev;
}				t_tkn;

//1 - собираем все токены в один лист
//cmds = ft_pipe_separator(str);

typedef struct	s_file
{
	char	*name;
	int		type; //<-3 <<-5 >-4 >>-6
	t_file	*next;
}				t_file;

typedef struct	s_cmd
{
	char	**cmd;
	t_file	*begin_redirs;
	t_cmd	*next;
//	t_tkn	*prev;
}				t_cmd;

t_file	*ft_file_init(char *name, int type)//передаваемое имя уже замаллочено как надо
{
	//инициализирует файл с атрибутами, заполняет нужные значения и возвращает его адрес
	t_file	*new_file;

	if (!name)
		return (NULL);
	new_file = (t_file *)malloc(sizeof(t_file));
	if (!new_file)
		return (NULL);
	new_file->name = name;
	new_file->type = type;
	new_file->next = NULL;
	return (new_file);
}

t_cmd	*ft_cmd_init(t_file *begin_redirs, char **cmd)
{
	//инициализирует команду с атрибутами, заполняет нужные значения и возвращает её адрес
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd = cmd;
	new_cmd->begin_redirs = begin_redirs;
	new_cmd->next = NULL;
	return (new_cmd);
}

void	ft_free_cmd(t_cmd	*tkn)
{
	if (tkn->cmd)
		ft_free_tab(tkn->cmd);
	if (tkn->begin_redirs)
		ft_free_file_list(tkn->begin_redirs);
	free(tkn);
}

void	ft_free_file(t_file	*tkn)
{
	if (tkn->name)
		free(tkn->name);
	free(tkn);
}

t_file	**ft_free_file_list(t_file **begin_file)
{
	//проверяет, передали ли начало и если да, то фришит строки и токены

	t_file	*active;
	t_file	*prev;

	if (!*begin_file)
		return (NULL);
	active = *begin_file;
	prev = active;
	while (active->next)
	{
		active = active->next;
		ft_free_file(prev);
		prev = active;
	}
	ft_free_file(active);
	*begin_file = NULL;
	return (NULL);
}

t_cmd	**ft_free_cmd_list(t_cmd **begin_cmd)
{
	//проверяет, передали ли начало и если да, то фришит строки и токены

	t_cmd	*active;
	t_cmd	*prev;

	if (!*begin_cmd)
		return (NULL);
	active = *begin_cmd;
	prev = active;
	while (active->next)
	{
		active = active->next;
		ft_free_cmd(prev);
		prev = active;
	}
	ft_free_cmd(active);
	*begin_cmd = NULL;
	return (NULL);
}

t_file	**ft_file_add_back(t_file *new_file, t_file **begin_file)
{
	//функция проверяет, передали ли новый и если начало не 0, добавляет его в конец, а если 0 - возвращает новый как начало
	t_file	*last;

	if (!new_file)
		return (ft_free_file_list(begin_file));
	last = *begin_file;
	if (!last)
	{
		begin_file = &new_file;
		return (begin_file);
	}
	while (last->next)
		last = last->next;
	last->next = new_file;
	return (begin_file);
}

t_cmd	**ft_cmd_add_back(t_cmd *new_cmd, t_cmd **begin_cmd)
{
	//функция проверяет, передали ли новый и если начало не 0, добавляет его в конец, а если 0 - возвращает новый как начало
	t_cmd	*last;

	if (!new_cmd)
		return (ft_free_cmd_list(begin_cmd));
	last = *begin_cmd;
	if (!last)
	{
		begin_cmd = &new_cmd;
		return (begin_cmd);
	}
	while (last->next)
		last = last->next;
	last->next = new_cmd;
	return (begin_cmd);
}


//	t_cmd	*cmd_begin;

//	if (!ft_cmd_add_back(ft_cmd_init('0', 0), &cmd_begin));//инициализация первого псевдотокена. не забыть удалить
//		return (NULL);


t_cmd	**ft_line_tokenizer(char *str, t_cmd **cmd_begin, char **env)
{
	//перед вызовом этой функции проверить, что строка не пустая
	//функция создаёт токены команд в список из существующего строчного инпута
	//сначала разбивает по пайпам, а потом обрабатывает каждую область отдельно
	t_tkn	*tkn_begin;
	t_tkn	*tkn_blanc;
	char	**cmds;
	char	**first_cmd;

	cmds = ft_pipe_separator(str);
	first_cmd = cmds;
	while (*cmds)
	{
		if (!ft_tkn_add_back(ft_symb_tkn_init('0', 0), &tkn_begin)
			|| !ft_command_tokenizer(*(cmds++), &tkn_begin))//инициализация первого псевдотокена. не забыть удалить
			return (ft_free_tab(first_cmd));
		tkn_blanc = tkn_begin;
		tkn_begin = tkn_begin->next;
		ft_free_tkn(tkn_blanc);//удаление псевдотокена
		if(!ft_cmd_add_back(ft_cmd_filler(&tkn_begin, env), cmd_begin))
			return (NULL);
		ft_free_tkn_list(&tkn_begin);//освобождение листа токенов
	}
	ft_free_tab(first_cmd);
}

// int	ft_cmd_is_null(t_cmd *cmd)
// {
// 	int	flag;

// 	flag == 1;
// 	flag *= cmd->?? == NULL;
// 	//...
// 	return (flag);
// }

//--также нужна функция для обработки $с буквами в переменную, а с ? - в код последней ошибки, $$ - pid??

//2 - последовательно идём по токенам и заполняем t_cmd, раскрывая ковычки (у хердока без подмен вообще)
// если после токена нет информативного, выдаём соответствующую ошибку
//> < >> << |

int ft_is_redir(int type)
{
	return (type == 3 || type == 4 || type == 5|| type == 6);
}

void	ft_tkn_del(t_tkn *tkn, t_tkn **begin_tkn)//надо написать удаление текста из токенов. похоже нужно будет поле предыдущий в токенах
{
	t_tkn	*prev;
	t_tkn	*next;

	prev = tkn->prev;
	next = tkn->next;
	if (prev)
		prev->next = next;
	else
	{
		if (next)
			*begin_tkn = tkn->next;
		else
			*begin_tkn = NULL;
	}
	if (next)
		next->prev = prev;
	ft_free_tkn(tkn);
}

char	*ft_filename(t_tkn *tkn, t_tkn **begin_tkn)
{
	//функция копирует поле имя для файлов из токена в новый маллок
	//дополнительно проверяя, чтобы файл не кончился и был токен с названием
	char	*name;
	t_tkn	*tkn_ptr;
	int		len;

	if (!tkn->next)
	{
		//ошибка раннего конца строки; для экономии строк ретурн функции ошибки
		g_error = 1;
		return (NULL);
	}
	tkn_ptr = tkn->next;
	while (tkn_ptr->type == 7 && tkn_ptr->next)//space
		tkn_ptr = tkn_ptr->next;
	if (tkn_ptr->type == 7)
	{
		//ошибка раннего конца строки; для экономии строк ретурн функции ошибки
		g_error = 1;
		return (NULL);
	}
	if (tkn_ptr->type != 1)
	{
		//ошибка около tkn_ptr->type   ft_error_near(); для экономии строк ретурн функции ошибки
		//g_error = 1 внутри ф-ции;
		return (NULL);
	}
	len = ft_strlen(tkn_ptr->value);
	name = (char *)malloc((len + 1) * sizeof(char));
	if (!name)
		return (NULL);
	ft_strlcpy(name, tkn_ptr->value, len + 1);
	ft_tkn_del(tkn_ptr, begin_tkn);
	return (name);
}

ft_tkn_prev_setter(t_tkn **tkn_begin)
{
	//проставляет файлам значение поле "предыдущий"
	t_tkn	*prev;

	while (*tkn_begin && (*tkn_begin)->next)
	{
		prev = tkn_begin;
		tkn_begin = (*tkn_begin)->next;
		(*tkn_begin)->prev = prev;
	}
}

int	ft_numlen(int n)
{
	//считает длину числа в символах
	int		count;

	if (n <= 0)
	{
		count = 1;
		n *= -1;
	}
	else
		count = 0;
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

int	ft_var_len(char **str, char **env)
{
	int		len;
	char	*ptr;

	ptr = *str;
	len = 0;
	while (ft_isalnum(*ptr) || *ptr == '_')
	{
		ptr++;
		len++;
	}
	ptr = NULL;
	while (*env)
	{
		if (!ft_strncmp(*str, *env, len) && *(*env + len) == '=')
			ptr = (*env) + len + 1;
		env++;
	}
	(*str) += len;
	return (ft_strlen(ptr));
}

int ft_is_opening_or_closing_quote(char c, int qt)
{
	//проверяет, является ли символ реальными открывающими или закрывающими скобками
	if ((c == '"' && (!qt || qt == 2)) || (c == '\'' && (!qt || qt == 1)))
		return 1;
	else
		return 0;
}

int	ft_file_len_counter(t_file *file, char **env)
{
	//считает длину строки, которая получится для имени файла после раскрытия ковычек
	char	*str;
	int		len;
	int		quote_type;

	quote_type = 0;
	len = 0;
	str = file->name;
	while (str && *str)
	{
		if (ft_is_opening_or_closing_quote(*str, quote_type))
			quote_type = ft_quotes_identifier(str++, quote_type);
		else if (*str == '$' && (!quote_type || !quote_type == 2) && file->type != 5)
		{
			if (*(++str) == '?')
			{
				len += ft_numlen(g_error);
				str++;
			}
			else
				len += ft_var_len(&(str), env);
		}
		else
			len++;
	}
	return (len);
}

char *ft_fill_last_err(char *name, char **str)
{
	//заполняет в имя номер посл ошибки итоа и возвращает адрес первого незаполненного символа, делает (*str)++
	char	*num;
	int		i;

	num = NULL;
	i = 0;
	while (!num && i++ < 5)
		num = ft_itoa(g_error);
	(*str)++;
	i = 0;
	while (num[i])
		*(name++) = num[i++];
	free(num);
	return (name);
}

char	*ft_fill_var_value(char **str, char *name, char **env)
{
	//ищет перем по имени из букв до не (словоцифры или НП), заполняет имя её значением и сдвигает строку
	int		len;
	char	*ptr;

	ptr = *str;
	len = 0;
	while (ft_isalnum(*ptr) || *ptr == '_')
	{
		ptr++;
		len++;
	}
	ptr = NULL;
	while (*env)
	{
		if (!ft_strncmp(*str, *env, len) && *(*env + len) == '=')
			ptr = (*env) + len + 1;
		env++;
	}
	(*str) += len;
	while (ptr && *ptr)
		*(name++) = *(ptr++);
	return (name);
}

char	*ft_dequote_file_name(t_file *file, char *name, char **env)
{
	//раскрывает скобки в названии файла в заранее замало ченную переменную нужного размера
	char	*str;
	int		quote_type;

	quote_type = 0;
	str = file->name;
	while (str && *str)
	{
		if (ft_is_opening_or_closing_quote(*str, quote_type))
			quote_type = ft_quotes_identifier(str++, quote_type);
		else if (*str == '$' && (!quote_type || !quote_type == 2) && file->type != 5)
		{
			if (*(++str) == '?')
				name = ft_fill_last_err(name, &str);
			else
				name = ft_fill_var_value(&str, name, env);
		}
		else
			*(name++) = *(str++);
	}
	return (name);
}

t_file	*ft_file_dequoter(t_file *file, char **env)
{
	//раскрывает скобки в названии файла
	int		len;
	char	*name;

	if (file->name)
	{
		len = ft_file_len_counter(file, env);
		name = (char *)malloc((len + 1) * sizeof(char));
		if (!name)
			return (NULL);
		name[len] = '\0';
		name = ft_dequote_file_name(file, name, env);
		free(file->name);
		file->name = name;
	}
	return (file);
}

t_file	**ft_dequote_file_list(t_file **redir_begin, char **env)
{
	//раскроетывает скобки в названиях файлов
	t_file	*file;

	file = *redir_begin;
	while (file->next)
	{
		if (!ft_file_dequoter(file, env))
			return (ft_free_file_list(redir_begin));
		file = file->next;
	}
	if (!ft_file_dequoter(file, env))
		return (ft_free_file_list(redir_begin));
	return (redir_begin);
}

//////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

int	ft_tkn_len_counter(t_tkn *tkn, char **env)
{
	//считает длину строки, которая получится для имени файла после раскрытия ковычек
	char	*str;
	int		len;
	int		quote_type;

	quote_type = 0;
	len = 0;
	str = tkn->value;
	while (str && *str)
	{
		if (ft_is_opening_or_closing_quote(*str, quote_type))
			quote_type = ft_quotes_identifier(str++, quote_type);
		else if (*str == '$' && (!quote_type || !quote_type == 2) && tkn->type != 5)
		{
			if (*(++str) == '?')
			{
				len += ft_numlen(g_error);
				str++;
			}
			else
				len += ft_var_len(&(str), env);
		}
		else
			len++;
	}
	return (len);
}

char	*ft_dequote_file_name(t_tkn *tkn, char *value, char **env)
{
	//раскрывает скобки в названии файла в заранее замало ченную переменную нужного размера
	char	*str;
	int		quote_type;

	quote_type = 0;
	str = tkn->value;
	while (str && *str)
	{
		if (ft_is_opening_or_closing_quote(*str, quote_type))
			quote_type = ft_quotes_identifier(str++, quote_type);
		else if (*str == '$' && (!quote_type || !quote_type == 2) && tkn->value != 5)
		{
			if (*(++str) == '?')
				value = ft_fill_last_err(value, &str);
			else
				value = ft_fill_var_value(&str, value, env);
		}
		else
			*(value++) = *(str++);
	}
	return (value);
}

t_tkn	*ft_tkn_dequoter(t_tkn *tkn, char **env)
{
	//раскрывает скобки в названии файла
	int		len;
	char	*value;

	if (tkn->value)
	{
		len = ft_tkn_len_counter(tkn, env);
		value = (char *)malloc((len + 1) * sizeof(char));
		if (!value)
			return (NULL);
		value[len] = '\0';
		value = ft_dequote_tkn_value(tkn, value, env);
		free(tkn->value);
		tkn->value = value;
	}
	return (tkn);
}

t_tkn	**ft_dequote_tkn_list(t_tkn **tkn_begin, char **env)
{
	//раскроетывает скобки в оставшихся командах
	t_tkn	*tkn;
	t_tkn	*res;

	tkn = *tkn_begin;
	while (tkn->next)
	{
		while (tkn->type == 7 && tkn->next)
		{
			res = tkn;
			tkn = tkn->next;
			ft_tkn_del(res, tkn_begin);
		}
		if (tkn->type != 1)
			printf("Something other than vords token left in list");//<<<=========
		if (!ft_tkn_dequoter(tkn, env))
			return (ft_free_tkn_list(tkn_begin));
		tkn = tkn->next;
	}
	if (!ft_tkn_dequoter(tkn, env))
		return (ft_free_tkn_list(tkn_begin));
	return (tkn_begin);
}

char	**ft_init_tab(char ***cmd, int i, t_tkn **tkn_begin)
{
	int	n;
	int	len;
	t_tkn	*tkn;

	n = 0;
	tkn = *tkn_begin;
	*cmd = (char **)malloc(sizeof(char*) * (i + 1));
	if(!*cmd)
		return(NULL);
	(*cmd)[i] = NULL;
	while (n < i)
	{
		if (tkn->type = 1)
		{
			len = ft_strlen(tkn->value);
			(*cmd[n]) = ft_strdup(tkn->value);
			if(!(*cmd)[n++])
				return(ft_free(*cmd));
		}
		if (tkn->next)
			tkn = tkn->next;
	}
	return (*cmd);
}

char	**ft_list_to_tab(t_tkn	**tkn_begin, char ***cmd)
{
//функция для заполнения **cmd для отработки команды
	int		i;
	t_tkn	*tkn;
//1 - посчитать количество токенов слов
	tkn = *tkn_begin;
	if (tkn)
		i = 1;
	else
		i = 0;
	while (tkn && tkn->next)
	{
		if (tkn->type == 1)
			i++;
		tkn = tkn->next;
	}
//2 - выделить память под таблицу и окопируем слова в таблицу
	*cmd = ft_init_tab(cmd, i, tkn_begin);
	if (!*cmd)
		return(ft_free_tkn_list(tkn_begin));
//4 - фришим о обнуляем токен
	return (*cmd);
}

t_cmd	*ft_cmd_filler(t_tkn **tkn_begin, char **env)
{
	//функция должна наполнять токен команды (и токен редиректа) полноценным содержимым
	t_tkn	*tkn;
	t_cmd	*cmdt;
	t_file	*redir_begin;
	char	**cmd;

	tkn = *tkn_begin;
	ft_tkn_prev_setter(tkn_begin);
	while (tkn->next)
	{
		if (ft_is_redir(tkn->type))
			if (!ft_file_add_back(ft_file_init(ft_filename(tkn, tkn_begin), tkn->type), &redir_begin))
				return (ft_free_tkn_list(tkn_begin));
		tkn = tkn->next;
	}
	if (ft_is_redir(tkn->type))
		if (!ft_file_add_back(ft_file_init(ft_filename(tkn, tkn_begin), tkn->type), &redir_begin))
			return (ft_free_tkn_list(tkn_begin));
	if (!ft_dequote_file_list(&redir_begin, env))
		return (ft_free_tkn_list(tkn_begin));
	if (!ft_dequote_tkn_list(&tkn_begin, env))
		return (ft_free_file_list(&redir_begin));
	if (!ft_list_to_tab(&tkn_begin, &cmd))
		return (ft_free_file_list(&redir_begin));
	cmdt = ft_cmd_init(redir_begin, cmd);
	if (!cmdt);
		return (NULL);
	return (cmdt);
}


// *предполагаем, что ошибка двух последовательных токенов пайпа уже проверена

//3 - получаем список t_cmd   если звёздочка не раскрыта, то тут можно проверить на абсолютно пустой цмд

//4 - исполняем пайп
//4.1 - реализуем перенаправления
