#include "../minishell.h"

char	**ft_init_tab(char ***cmd, int i, t_tkn **tkn_begin)
{
	int	n;
//	int	len;
	t_tkn	*tkn;

	n = 0;
	tkn = *tkn_begin;
	*cmd = (char **)malloc(sizeof(char*) * (i + 1));
	if(!*cmd)
		return(NULL);
	(*cmd)[i] = NULL;
	while (n < i)//ошибки возникать не должно если хорошо посчитано кол-во типов 1
	{
		if (tkn->type == 1)
		{
//			len = ft_strlen(tkn->value);
			((*cmd)[n]) = ft_strdup(tkn->value);
			if(!(*cmd)[n++])
				return(ft_free(*cmd));
		}
		// write(1, "a\n", 2);//=======================
		if (tkn->next)
			tkn = tkn->next;
	}
	return (*cmd);
}

//функция для заполнения **cmd для отработки команды
char	**ft_list_to_tab(t_tkn	**tkn_begin, char ***cmd)
{
	int		i;
	t_tkn	*tkn;
//1 - посчитать количество токенов слов
	tkn = *tkn_begin;
	if (tkn && tkn->type != 0)
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
	// write(1, "a\n", 2);//=======================
	if (tkn->type == 0)
		ft_tkn_del(tkn, tkn_begin);
	if (!*cmd)
	{
		ft_free_tkn_list(tkn_begin);
		return(NULL);
	}
//4 - фришим о обнуляем токен
	return (*cmd);
}

//функция должна наполнять токен команды (и токен редиректа) полноценным содержимым
t_cmd	*ft_cmd_filler(t_tkn **tkn_begin, char **env)
{
	t_tkn	*tkn;
	t_cmd	*cmdt = NULL;
	t_file	*redir_begin;
	char	**cmd = NULL;

	redir_begin = NULL;
	tkn = *tkn_begin;
	ft_tkn_prev_setter(tkn_begin);
	while (tkn->next)
	{
		if (ft_is_redir(tkn->type))
		{
			if (!ft_file_add_back(ft_file_init(ft_filename(tkn, tkn_begin), tkn->type), &redir_begin))
			{
				ft_free_tkn_list(tkn_begin);
				return (NULL);
			}
			ft_tkn_del(tkn, tkn_begin);
		}
		if (tkn->next)
			tkn = tkn->next;
	}
	if (ft_is_redir(tkn->type))
	{
		if (!ft_file_add_back(ft_file_init(ft_filename(tkn, tkn_begin), tkn->type), &redir_begin))
		{
			ft_free_tkn_list(tkn_begin);
			return (NULL);
		}
		ft_tkn_del(tkn, tkn_begin);
	}
	if (redir_begin)
	{
		if (!ft_dequote_file_list(&redir_begin, env))
		{
			ft_free_tkn_list(tkn_begin);
			return (NULL);
		}
	}
//	write(1, "\ntkn\n", 5);//=======================
//	ft_print_tkn(*tkn_begin);
//	write(1, "\n\n", 2);//=======================
	if (!ft_dequote_tkn_list(tkn_begin, env))
	{
		ft_free_file_list(&redir_begin);
		return (NULL);
	}
//	ft_print_file2(redir_begin);
//	ft_print_cmd(cmd);
	if (!ft_list_to_tab(tkn_begin, &cmd))
	{
	// write (1, "her2\n", 5);
		ft_free_file_list(&redir_begin);
		return (NULL);
	}
	cmdt = ft_cmd_init(redir_begin, cmd);
	if (!cmdt)
		return (NULL);
	return (cmdt);
}
