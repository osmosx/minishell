/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:22:18 by keaton            #+#    #+#             */
/*   Updated: 2022/08/07 21:05:03 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//раскрывает скобки в названии файла в заранее замалоченную
// переменную нужного размера
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
		else if (*str == '$' && quote_type != 1 && file->type != 5)
		{
			if (*(++str) == '?')
				name = ft_fill_last_err(name, &str);
			else if (*str && !ft_isspace(*str) && !ft_is_opening_or_closing_quote(*str, quote_type))
				name = ft_fill_var_value(&str, name, env);
			else
				*(name++) = '$';
		}
		else
			*(name++) = *(str++);
	}
}

//раскрывает скобки в названии файла
t_file	*ft_file_dequoter(t_file *file, char **env)
{
	int		len;
	char	*name;

	if (file->name)
	{
		len = ft_file_len_counter(file, env);
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
		error_print(1, "no redirections error");
		return (NULL);
	}
	file = *redir_begin;
	while (file && file->next)
	{
		if (!ft_file_dequoter(file, env))
			return (ft_free_file_list(redir_begin));
		file = file->next;
	}
	if (!ft_file_dequoter(file, env))
		return (ft_free_file_list(redir_begin));
	return (redir_begin);
}
