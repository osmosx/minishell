#include "../minishell.h"

void	ft_free_file(t_file	*tkn)
{
	if (tkn->name)
		free(tkn->name);
	free(tkn);
}

//проверяет, передали ли начало и если да, то фришит строки и токены
t_file	**ft_free_file_list(t_file **begin_file)
{

	t_file	*active;
	t_file	*prev;

	if (!*begin_file)
		return (NULL);
	// write (1, "here\n", 5);
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

//инициализирует файл с атрибутами, заполняет нужные значения и возвращает его адрес
t_file	*ft_file_init(char *name, int type)//передаваемое имя уже замаллочено как надо
{
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

//функция проверяет, передали ли новый и если начало не 0, добавляет его в конец, а если 0 - возвращает новый как начало
t_file	**ft_file_add_back(t_file *new_file, t_file **begin_file)
{
	t_file	*last;

	if (!new_file)
		return (ft_free_file_list(begin_file));
	last = *begin_file;
	if (!last)
	{
		*begin_file = new_file;
		return (begin_file);
	}
	while (last->next)
		last = last->next;
	last->next = new_file;
	return (begin_file);
}

int	ft_is_redir(int type)
{
	return (type == 3 || type == 4 || type == 5 || type == 6);
}

//функция копирует поле имя для файлов из токена в новый маллок
//дополнительно проверяя, чтобы файл не кончился и был токен с названием
char	*ft_filename(t_tkn *tkn, t_tkn **begin_tkn)
{
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
//	ft_tkn_del(tkn, begin_tkn);
	ft_tkn_del(tkn_ptr, begin_tkn);
	return (name);
}

//считает длину строки, которая получится для имени файла после раскрытия ковычек
int	ft_file_len_counter(t_file *file, char **env)
{
	char	*str;
	int		len;
	int		quote_type;

//	write(1, "here<-\n", 5);//=======================
	quote_type = 0;
	len = 0;
	str = file->name;
	while (str && *str)
	{
		if (ft_is_opening_or_closing_quote(*str, quote_type))
			quote_type = ft_quotes_identifier(str++, &quote_type);
		else if (*str == '$' && (!quote_type || !(quote_type == 2)) &&
		file->type != 5)
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
		{
			len++;
			str++;
		}
	}
	return (len);
}
