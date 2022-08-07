#include "minishell.h"

//-----------parser


// void	ft_printtab(char **cmds)
// {
// 	if (!cmds)
// 		printf("No cmds tab");
// 	else
// 		while (*cmds)
// 			printf("%s\n", *(cmds++));
// }

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
	if (tkn == NULL)
		printf("tkn NULL\n");
	else
	{
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
}

void	ft_print_file(t_file **file_begin)
{
	t_file	**tkn;

	tkn = file_begin;
	if (tkn == NULL)
		printf("file NULL\n");
	else
	{
		while ((*tkn)->next)
		{
			printf("type = %d\n", (*tkn)->type);
			if ((*tkn)->name)
				printf("value = %s\n", (*tkn)->name);
			(*tkn) = (*tkn)->next;
		}
		printf("type = %d\n", (*tkn)->type);
		if ((*tkn)->name)
			printf("value = %s\n", (*tkn)->name);
	}
}
void	ft_print_file2(t_file *file_begin)
{
	t_file	*tkn;

	tkn = file_begin;
	if (tkn == NULL)
		printf("file NULL\n");
	else
	{
		while (tkn->next)
		{
			printf("type = %d\n", tkn->type);
			if (tkn->name)
				printf("value = %s\n", tkn->name);
			tkn = tkn->next;
		}
		printf("type = %d\n", tkn->type);
		if (tkn->name)
			printf("value = %s\n", tkn->name);
	}
}
void	ft_print_cmd(t_cmd *cmd)
{
	t_cmd	*tkn;

	tkn = cmd;
	if (tkn == NULL)
		printf("cmd NULL\n");
	else
	{
		while (tkn->next)
		{
			ft_printtab(tkn->cmd);
			ft_print_file2(tkn->begin_redirs);
			tkn = tkn->next;
			write(1,"\n",1);
		}
		ft_printtab(tkn->cmd);
		ft_print_file2(tkn->begin_redirs);
	}
}

/*
int	main(int argc, char **argv, char** env)
{
	t_tkn	*tkn_begin;
//	t_file	*begin_file;
	// t_file	*redir_begin = NULL;
	char	**cmds;
	char	*str =  ">>hi >ome |command 	\"with brac|es$SHELLs\" 'of both ty|pes$SHELLs' >and| << arrows";
//	char	*str =  "hi ome |command \"with brac|es$SHELLs\" 'of both ty|pes$SHELLs' and| arrows";
	t_cmd	*cmd;

	if (argc)
		ft_printtab(argv);
	tkn_begin = NULL;
	cmds = ft_pipe_separator(str);
	ft_printtab(cmds);
	while (*cmds)
	{
		ft_command_tokenizer(*(cmds++), &tkn_begin);
	}
	ft_print_tkn(tkn_begin);
	ft_tkn_prev_setter(&tkn_begin);
	//printf("%s", ft_filename(tkn_begin, &tkn_begin));
	cmd = ft_cmd_filler(&tkn_begin, env);
	write(1,"\n", 1);
	// ft_print_file2(ft_file_init(ft_filename(tkn_begin, &tkn_begin), tkn_begin->type));
	// ft_print_file(ft_file_add_back(ft_file_init(ft_filename(tkn_begin, &tkn_begin), tkn_begin->type), &redir_begin));
	write(1,"\n", 1);

	ft_print_tkn(tkn_begin);
	write (1, "\ncmd\n", 5);
	ft_print_cmd(cmd);
	ft_free_tkn_list(&tkn_begin);
	printf("free\n");
	ft_print_tkn(tkn_begin);
	ft_printtab(cmds);
}*/

/*
//---------------main
int	main(int argc, char **argv, char** env)
{
//	t_tkn	*tkn_begin;
//	t_file	*begin_file;
	// t_file	*redir_begin = NULL;
	char	**cmds;
	// char	*str =  ">>hi$SHELL cmd >ome |command 	\"with brac|es$SHELLs\" 'of both ty|pes$SHELLs' >and| << arrows";
	// char	*str =  "hi ome |command \"with brac|es$SHELLs\" 'of both ty|pes$SHELLs' and| arrows";
	char *str = "";
	t_cmd	*cmd_begin = NULL;

	if (argc)
		ft_printtab(argv);//--------------------
	cmds = ft_line_tokenizer(str, &cmd_begin, env);
	if (!cmds)
	{
		ft_free_cmd_list(&cmd_begin);//и ошибку поставить
	}
	ft_printtab(cmds);
	write (1, "\ncmd\n", 5);
	ft_print_cmd(cmd_begin);
}
*/