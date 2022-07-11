#include "../minishell.h"

void	ft_free_cmd(t_cmd	*tkn)
{
	if (tkn->cmd)
		ft_free(tkn->cmd);
	if (tkn->begin_redirs)
		ft_free_file_list(&tkn->begin_redirs);
	free(tkn);
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

t_cmd	**ft_cmd_add_back(t_cmd *new_cmd, t_cmd **begin_cmd)
{
	//функция проверяет, передали ли новый и если начало не 0, добавляет его в конец, а если 0 - возвращает новый как начало
	t_cmd	*last;

	write(1,"new cmd\n", 8);
//	ft_print_cmd(new_cmd);
	if (!new_cmd)
		return (ft_free_cmd_list(begin_cmd));
	last = *begin_cmd;
	if (!last)
	{
		*begin_cmd = new_cmd;
		return (begin_cmd);
	}
	while (last->next)
		last = last->next;
	last->next = new_cmd;
	return (begin_cmd);
}
