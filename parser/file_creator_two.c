/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_creator_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:22:06 by keaton            #+#    #+#             */
/*   Updated: 2022/08/07 21:26:43 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_redir(int type)
{
	return (type == 3 || type == 4 || type == 5 || type == 6);
}

char	*ft_deferrtype(t_tkn *tkn)
{
	if (!tkn)
		return (ft_strdup("`newline'"));
	if (tkn->type == 2)
		return (ft_strdup("`|'"));
	if (tkn->type == 3)
		return (ft_strdup("`<'"));
	if (tkn->type == 4)
		return (ft_strdup("`>'"));
	if (tkn->type == 5)
		return (ft_strdup("`<<'"));
	if (tkn->type == 6)
		return (ft_strdup("`>>'"));
	return ("");
}

void	*error_near_print(int err_num, t_tkn *tkn)
{
	char	*err_char;
	char	*name;

	g_error = err_num;
	name = ft_deferrtype(tkn);
	if (!name)
		return (NULL);
	err_char = ft_strjoin("minishell: syntax error near unexpected token ",
			name);
	free(name);
	if (!err_char)
		return (NULL);
	write(2, err_char, ft_strlen(err_char));
	write(2, "\n", 1);
	free(err_char);
	return (NULL);
}

//функция копирует поле имя для файлов из токена в новый маллок
//дополнительно проверяя, чтобы файл не кончился и был токен с названием
char	*ft_filename(t_tkn *tkn, t_tkn **begin_tkn)
{
	char	*name;
	t_tkn	*tkn_ptr;
	int		len;

	if (!tkn->next)
		return (error_near_print(1, tkn->next));
	tkn_ptr = tkn->next;
	while (tkn_ptr->type == 7 && tkn_ptr->next)
		tkn_ptr = tkn_ptr->next;
	if (tkn_ptr->type == 7)
		return (error_near_print(1, tkn->next));
	if (tkn_ptr->type != 1)
		return (error_near_print(1, tkn->next));
	len = (int)ft_strlen(tkn_ptr->value);
	name = (char *)malloc((len + 1) * sizeof(char));
	if (!name)
		return (NULL);
	ft_strlcpy(name, tkn_ptr->value, len + 1);
	ft_tkn_del(tkn_ptr, begin_tkn);
	return (name);
}

//считает длину строки, которая получится для имени файла
// после раскрытия ковычек
int	ft_file_len_counter(t_file *file, char **env, int quote_type)
{
	char	*str;
	int		len;

	len = 0;
	str = file->name;
	while (str && *str)
	{
		if (ft_is_opening_or_closing_quote(*str, quote_type))
			quote_type = ft_quotes_identifier(str, &quote_type);
		else if (*str == '$' && quote_type != 1 && file->type != 5)
		{
			if (*(++str) == '?')
				len += ft_numlen(g_error);
			else if (*str && !ft_isspace(*str)
				&& !ft_is_opening_or_closing_quote(*str, quote_type))
				len += ft_var_len(&str, env);
			else
				len++;
		}
		else
			len++;
		if (*str)
			str++;
	}
	return (len);
}
