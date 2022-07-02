#include "../minishell.h"

//-----------parser


void	ft_printtab(char **cmds)
{
	while (*cmds)
	{
		printf("%s\n", *(cmds++));
	}
}

/*
char	**ft_free(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free (arr);
	return (NULL);
}
int	main()
{
	char	**cmds;
	char	*str =  "s ome |command \"with brac|es\" 'of both ty|pes' >and| << arrows";

	cmds = NULL;
	// printf("%s\n", str);
	// write(1, "-", 1);

	cmds = ft_pipe_separator(str);
	ft_printtab(cmds);
	ft_free(cmds);
}
*/

//-----------tkn_utils

void	ft_print_tkn(t_tkn *tkn_begin)
{
	t_tkn	*tkn;

	tkn = tkn_begin;
	while (tkn->next)
	{
		printf("type = %d\n", tkn->type);
		if (tkn->value)
			printf("value = %s\n", tkn->value);
		tkn = tkn->next;
	}
	printf("type = %d\n", tkn->type);
	if (tkn->value)
		printf("value = %s\n", tkn->value);
}

int	main()
{
	t_tkn	*tkn_begin;
	char	**cmds;
	char	*str =  ">> >ome |command \"with brac|es\" 'of both ty|pes' >and| << arrows";

	tkn_begin = NULL;
	cmds = ft_pipe_separator(str);
	ft_printtab(cmds);
	while (*cmds)
	{
		ft_command_tokenizer(*(cmds++), &tkn_begin);
	}
	ft_print_tkn(tkn_begin);
	ft_printtab(cmds);
}
