/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_creator_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:22:06 by keaton            #+#    #+#             */
/*   Updated: 2022/07/16 20:22:07 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		return (error_print(1, ""));
	tkn_ptr = tkn->next;
	while (tkn_ptr->type == 7 && tkn_ptr->next)
		tkn_ptr = tkn_ptr->next;
	if (tkn_ptr->type == 7)
		return (error_print(1, ""));
	if (tkn_ptr->type != 1)
		return (error_print(1, ""));
	len = ft_strlen(tkn_ptr->value);
	name = (char *)malloc((len + 1) * sizeof(char));
	if (!name)
		return (NULL);
	ft_strlcpy(name, tkn_ptr->value, len + 1);
	ft_tkn_del(tkn_ptr, begin_tkn);
	return (name);
}

//считает длину строки, которая получится для имени файла
// после раскрытия ковычек
int	ft_file_len_counter(t_file *file, char **env)
{
	char	*str;
	int		len;
	int		quote_type;

	quote_type = 0;
	len = 0;
	str = file->name;
	while (str && *str)
	{
		if (ft_is_opening_or_closing_quote(*str, quote_type))
			quote_type = ft_quotes_identifier(str++, &quote_type);
		else if (*str == '$' && (!quote_type || quote_type != 2)
			&& file->type != 5)
		{
			if (*(++str) == '?')
				len += ft_numlen(g_error);
			else
				len += ft_var_len(&str, env);
		}
		else
			len++;
		str++;
	}
	return (len);
}

