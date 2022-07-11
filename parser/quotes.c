#include "../minishell.h"

//раскрывает скобки в названии файла в заранее замало ченную переменную нужного размера
void	ft_dequote_file_name(t_file *file, char *name, char **env)
{
	char	*str;
	int		quote_type;

	quote_type = 0;
	str = file->name;
	while (str && *str)
	{
		if (ft_is_opening_or_closing_quote(*str, quote_type))
			quote_type = ft_quotes_identifier(str++, &quote_type);
		else if (*str == '$' && (!quote_type || !(quote_type == 2)) && file->type != 5)
		{
			if (*(++str) == '?')
				name = ft_fill_last_err(name, &str);
			else
				name = ft_fill_var_value(&str, name, env);
		}
		else
			*(name++) = *(str++);
	}
	//return (name);
}

//раскрывает скобки в названии файла
t_file	*ft_file_dequoter(t_file *file, char **env)
{
	int		len;
	char	*name;

	if (file->name)
	{
		len = ft_file_len_counter(file, env);
		// write(1, "here++\n", 5);//=======================
		// printf("len = %d\n", len);//===================
		name = (char *)malloc((len + 1) * sizeof(char));
		if (!name)
			return (NULL);
		name[len] = '\0';
		ft_dequote_file_name(file, name, env);
		free(file->name);
		file->name = name;
	}
	return (file);
}

//раскроетывает скобки в названиях файлов
t_file	**ft_dequote_file_list(t_file **redir_begin, char **env)
{
	t_file	*file;

	if (!*redir_begin)
	{
		write (1, "no redirections error", 21);
		return (NULL);
	}
	file = *redir_begin;
	while (file && file->next)
	{
		if (!ft_file_dequoter(file, env))
			return (ft_free_file_list(redir_begin));
		file = file->next;
	}
//	ft_print_file2(*redir_begin);
//	write(1, "here!-\n", 5);
	if (!ft_file_dequoter(file, env))
		return (ft_free_file_list(redir_begin));
	return (redir_begin);
}

//раскрывает скобки в названии файла в заранее замало ченную переменную нужного размера
void	ft_dequote_tkn_value(t_tkn *tkn, char *value, char **env)
{
	char	*str;
	int		quote_type;

	quote_type = 0;
	str = tkn->value;
//	write(1, "in tkn_deq1\n", 12);
	while (str && *str)
	{
		if (ft_is_opening_or_closing_quote(*str, quote_type))
			quote_type = ft_quotes_identifier(str++, &quote_type);
		else if (*str == '$' && (!quote_type || !(quote_type == 2)) &&
		tkn->type != 5)
		{
			if (*(++str) == '?')
				value = ft_fill_last_err(value, &str);
			else
				value = ft_fill_var_value(&str, value, env);
		}
		else
			*(value++) = *(str++);
	}
//	write(1, "in tkn_deq2\n", 12);
//	return (value);
}

//раскрывает скобки в названии файла
t_tkn	*ft_tkn_dequoter(t_tkn *tkn, char **env)
{
	int		len;
	char	*value;

	if (tkn && tkn->value)
	{
		len = ft_tkn_len_counter(tkn, env);
		value = (char *)malloc((len + 1) * sizeof(char));
		if (!value)
			return (NULL);
		value[len] = '\0';
		ft_dequote_tkn_value(tkn, value, env);
		free(tkn->value);
		tkn->value = value;
	}
//		write(1, "in tkn", 6);
	return (tkn);
}

//раскроетывает скобки в оставшихся командах
t_tkn	**ft_dequote_tkn_list(t_tkn **tkn_begin, char **env)
{
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
		if (tkn->type != 1 && tkn->type != 7)
			printf("Something other than words token left in list");//<<<=========
		if (!ft_tkn_dequoter(tkn, env))
			return (ft_free_tkn_list(tkn_begin));
		if (tkn->next)
			tkn = tkn->next;
//		write(1, "in deq\n", 7);
	}
	if (tkn->type == 7)
	{
		res = tkn;
		tkn = tkn->prev;
		ft_tkn_del(res, tkn_begin);
	}
	if (!tkn)
		return (ft_tkn_add_back(ft_symb_tkn_init('0', 0), tkn_begin));
	if (!ft_tkn_dequoter(tkn, env))
		return (ft_free_tkn_list(tkn_begin));
	return (tkn_begin);
}
