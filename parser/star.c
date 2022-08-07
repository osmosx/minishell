/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 23:08:06 by keaton            #+#    #+#             */
/*   Updated: 2022/08/08 00:34:17 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <dirent.h>
//opendir, readdir, closedir;

char	*ft_destar(char *buf, char *word_start)
{
	char			*word;
	char			*ptr;
	DIR				*dir;
	struct dirent	*entity;
	int				len;
	

	dir = opendir(".");
	if (dir ==NULL)
		return (1);
	entity = readdir(dir);
	while (entity != NULL)
	{
		word = word_start;
		ptr = entity->d_name;
		while (*word)
		{
			if (*word == "*")
			{
				len = 0;
				word++;
				while (*word || *word != '*')
					len++;
				ptr = strlstr(ptr, word, len);//looks for len-limited word in ptr-string. 
				//returns occurance. if len == 0 returns ptr;
				if (!ptr)
					break ;
			}
			if (*word && *(word++) != *(ptr++))
				break ;
		}
		entity = readdir(dir);
	}


	closedir(dir);
	return (buf);
}

int ft_star(char *str)
{
	char    *word_start;
	char    *str_start;
	int     len;
	char    *start;
	char    *word;
	char	*new;
	
	word_start = str;
	str_start = str;
	len = 0;
	while (*str)
	{
		if (str != str_start && ft_isspace(*(str - 1)))
			word_start = str;
		len++;
		if (*str == '*')
		{
			start = ft_strdup(str_start);
			start[len] = '\0';
			word = (char *)malloc(ft_wordlen(word_start) + 1);
			word = ft_destar(word, word_start);//destar word
			new = ft_strjoin(start, word);
			free (start);
			free (word);
			while (*str && !ft_isspace(*str))
				str++;
			word = new;
			new = ft_strjoin(new, str);
			free (word);
			free (str_start);
			str_start = new;
			free (new);
			str = str_start + len;
		}
	}
}