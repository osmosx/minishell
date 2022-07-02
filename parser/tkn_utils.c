#include "../minishell.h"

void	ft_free_tkn(t_tkn	*tkn)
{
	if (tkn->value)
		free(tkn->value);
	free(tkn);
}

t_tkn	**ft_free_tkn_list(t_tkn **begin_tkn)
{
	//проверяет, передали ли начало и если да, то фришит строки и токены
	t_tkn	*active;
	t_tkn	*prev;

	if (!*begin_tkn)
		return (NULL);
	active = *begin_tkn;
	prev = active;
	while (active->next)
	{
		active = active->next;
		ft_free_tkn(prev);
		prev = active;
	}
	ft_free_tkn(active);
	*begin_tkn = NULL;
	return (NULL);
}

/*
заглушка - 0
текст - 1
пайп - 2
< - 3
> - 4
<< - 5
>> - 6
пробел - 7
*/

int ft_def_token_type(char symb, int count)
{
	//определяет тип полученного символа для присвоения индекса токену
	int	type;

	type = 0; //это заглушка
	if (count == 1)
	{
		if (symb == '|')
			type = 2;
		else if (symb == '<')
			type = 3;
		else if (symb == '>')
			type = 4;
		else if (symb == ' ')
			type = 7;
	}
	else if (count == 2)
	{
		if (symb == '<')
			type = 5;
		else if (symb == '>')
			type = 6;
	}
	return (type);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\r' || c == '\f');
}

int	ft_is_symb_token(char c)
{
	return (c == '<' || c == '>' || c == '|');
}
