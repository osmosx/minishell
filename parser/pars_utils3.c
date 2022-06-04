//redirect implementation
typedef struct	s_tkn
{
	int		type;
	char	*value;
	t_tkn	*next;
//	t_tkn	*prev;
}				t_tkn;
#include "../minishell.h"

//1 - собираем все токены в один лист
cmds = ft_pipe_separator(str);

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

viod	ft_free_cmd(t_cmd	*tkn)
{
	if (tkn->cmd)
		ft_free_tab(tkn->cmd);
	if (tkn->begin_redirs)
		ft_free_file_list(tkn->begin_redirs);
	free(tkn);
}

viod	ft_free_file(t_cmd	*tkn)
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
		return (ft_free_cmd_list(begin_file));
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


	t_cmd	*cmd_begin;

	if (!ft_cmd_add_back(ft_cmd_init('0', 0), &cmd_begin));//инициализация первого псевдотокена. не забыть удалить
		return (NULL);


t_cmd	**ft_line_tokenizer(char *str, t_cmd **cmd_begin)
{
	//перед вызовом этой функции проверить, что строка не пустая
	//функция создаёт токены команд в список из существующего строчного инпута
	//сначала разбивает по пайпам, а потом обрабатывает каждую область отдельно
	t_tkn	*tkn_begin;
	t_tkn	*tkn_blanc;
	char	**cmds;

	cmds = ft_pipe_separator(str);
	while (*cmds)
	{
		if (!ft_tkn_add_back(ft_symb_tkn_init('0', 0), &tkn_begin)
			|| !ft_command_tokenizer(*(cmds++), &tkn_begin))//инициализация первого псевдотокена. не забыть удалить
			return (ft_free_tab(cmds));
		tkn_blanc = tkn_begin;
		tkn_begin = tkn_begin->next;
		ft_free_tkn(tkn_blanc);//удаление псевдотокена
		if(!ft_cmd_add_back(ft_cmd_filler(&tkn_begin), cmd_begin))
			return (NULL);
		ft_free_tkn_list(&tkn_begin);// освобождение листа токенов
	}
	ft_free_tab(cmds);
}

int	ft_cmd_is_null(t_cmd *cmd)
{
	int	flag;

	flag == 1;
	flag *= cmd->?? == NULL;
	//...
	return (flag);
}

//--также нужна функция для обработки $с буквами в переменную, а с ? - в код последней ошибки, $$ - pid??

//2 - последовательно идём по токенам и заполняем t_cmd, раскрывая ковычки (у хердока без подмен вообще)
// если после токена нет информативного, выдаём соответствующую ошибку
//> < >> << |

int ft_is_redir(int type)
{
	return (type == 3 || type == 4 || type == 5|| type == 6);
}



//////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

char	*ft_filename(t_tkn *tkn)
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
	ft_tkn_del(tkn_ptr)//надо написать удаление текста из токенов. похоже нужно будет поле предыдущий в токенах
	len = ft_strlen(tkn_ptr->value)
	name = (char *)malloc((len + 1) * sizeof(char))
	ft_strlcpy(name, tkn_ptr->value, len + 1)
	return (name)
}

t_cmd	*ft_cmd_filler(t_tkn **tkn_begin)
{
	//функция должна наполнять токен команды (и токен редиректа) полноценным содержимым
	t_tkn	*tkn;
	t_cmd	*cmdt;
	t_file	*redir_begin;
	char	**cmd;

	tkn = *tkn_begin;
	while (tkn->next)
	{
		if (ft_is_redir(tkn->type))
			if (!ft_file_add_back(ft_file_init(ft_filename(tkn), tkn->type), redir_begin))
				return (ft_free_tkn_list(tkn_begin));
	}
	//тут нужна функция, которая раскроет скобки в названиях файлов
	//тут нужна функция, которая раскроет скобки в оставшихся командах
	//и функция для заполнения **цмд
	cmdt = ft_cmd_init(redir_begin, cmd);
	if (!cmdt);
		return (NULL);
	return (cmdt);
}

// *предполагаем, что ошибка двух последовательных токенов пайпа уже проверена

//3 - получаем список t_cmd   если звёздочка не раскрыта, то тут можно проверить на абсолютно пустой цмд

//4 - исполняем пайп
//4.1 - реализуем перенаправления
