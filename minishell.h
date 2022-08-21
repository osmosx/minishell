/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:55:27 by nenvoy            #+#    #+#             */
/*   Updated: 2022/08/15 00:59:06 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/signal.h>
# include <errno.h>
# include <string.h>
# include <limits.h>
# include "./libft/libft.h"

//Для школы
# include <readline/readline.h>
# include <readline/history.h>

////Для дома
//# include "/usr/local/Cellar/readline/8.1.2/include/readline/readline.h"
//# include "/usr/local/Cellar/readline/8.1.2/include/readline/history.h"
// Вариант для Brew
// # include "/Users/nenvoy/.brew/Cellar/readline/8.1.2/include/readline/readline.h"
// # include "/Users/nenvoy/.brew/Cellar/readline/8.1.2/include/readline/history.h"

//Для Linux
//# include "/home/linuxbrew/.linuxbrew/Cellar/readline/8.1.2/include/readline/readline.h"
//# include "/home/linuxbrew/.linuxbrew/Cellar/readline/8.1.2/include/readline/history.h"

extern int	g_error;

typedef struct s_env
{
	char	**cp_env;
	char	**cp_path;
	char	**export;
}				t_env;

typedef struct s_tkn
{
	int				type;
	char			*value;
	struct s_tkn	*next;
	struct s_tkn	*prev;
}				t_tkn;

typedef struct s_file
{
	char			*name;
	int				type;
	struct s_file	*next;
}				t_file;

typedef struct s_cmd
{
	char			**cmd;
	int				pid;
	int				fd[2];
	t_file			*begin_redirs;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}				t_cmd;

// env utils
t_env	*init_env(t_env *envm, char **envp);
char	**copy_env(t_env *envm, char **env);
char	**unset_remove(t_env *envm, char *cmd);

// signal utils
void	ctrl_c(int signal);
void	ctrl_d(char *line, t_env *envm);
void	ctrl_backslash(int signal);
void	handler(int sig);
void	newline(int signal);

//built-in functions
int		builtins(char **cmd2, t_cmd *cmd, t_env	*env, int i);
int		m_pwd(void);
int		m_env(t_env *envm);
int		m_echo(char **cmd2);
int		m_exit(char **cmd, t_cmd *cmd_t, t_env *envm);
int		m_unset(t_env *envm, char **cmd2);
int		m_cd(t_env *envm, char *path);
int		m_export(t_env	*envm, char **cmd2);

//export utils
void	change_line_value(char **tab, char *new_str, int i);
int		find_line_in_tab(char **env, char *arg);
char	**add_line(char **arr, char *new_line);
char	**del_line(char **arr, int pos);
char	**con_twotab(char **tab, char **tab2);

//parser utils
char	**ft_fillcmds(char *str, char **cmds);
int		ft_quotes_identifier(char *str, int *quote_type);
int		ft_quotes_checker(char *str);
t_tkn	**ft_command_tokenizer(char *cmd, t_tkn **tkn_begin);
char	**ft_pipe_separator(char *str);
char	**ft_line_tokenizer(char *str, t_cmd **cmd_begin, char **env);
t_tkn	**ft_tkn_add_back(t_tkn *new_tkn, t_tkn **begin_tkn);
t_tkn	*ft_symb_tkn_init(char symb, int count);

//tkns
t_tkn	**ft_tkn(char **cmd, t_tkn **tkn_begin, char symb, int maxlen);
t_tkn	**ft_free_tkn_list(t_tkn **begin_tkn);
int		ft_def_token_type(char symb, int count);
int		ft_isspace(char c);
int		ft_is_symb_token(char c);
t_tkn	*ft_cmd_tkn_init(char **cmd);
void	ft_tkn_prev_setter(t_tkn *tkn_begin);
t_tkn	**ft_dequote_tkn_list(t_tkn **tkn_begin, char **env);
t_tkn	*ft_tkn_del(t_tkn *tkn, t_tkn **begin_tkn);
int		ft_tkn_len_counter(t_tkn *tkn, char **env);

//cmds
t_cmd	**ft_free_cmd_list(t_cmd **begin_cmd);
t_cmd	*ft_cmd_filler(t_tkn **tkn_begin, char **env);
t_cmd	*ft_cmd_init(t_file *begin_redirs, char **cmd);
t_cmd	**ft_cmd_add_back(t_cmd *new_cmd, t_cmd **begin_cmd);
void	ft_cmd_prev_setter(t_cmd *cmd_begin);

//files
t_file	**ft_file_add_back(t_file *new_file, t_file **begin_file);
t_file	*ft_file_init(char *name, int type);
char	*ft_filename(t_tkn *tkn, t_tkn **begin_tkn);
t_file	**ft_dequote_file_list(t_file **redir_begin, char **env);
t_file	**ft_free_file_list(t_file **begin_file);
char	*ft_fill_last_err(char *name, char **str);
char	*ft_fill_var_value(char **str, char *name, char **env);
int		ft_file_len_counter(t_file *file, char **env);

//utils
char	**ft_free(char **arr);
int		tablen(char **tab);
int		check_export_arg(char *cmd);
int		ft_is_redir(int type);
int		ft_is_opening_or_closing_quote(char c, int qt);
int		ft_numlen(int n);
int		ft_var_len(char **str, char **env);
void	*error_print(int err_num, char *err_char);
void	*error_near_print(int err_num, t_tkn *tkn);
void	ft_blanc(int sig);

//executor
void	ft_exec(t_cmd *cmd, t_env *env);
int		make_heredocs(t_cmd *cmd, t_env *env);
int		check_redirection(t_cmd *cmd, int quit);
void	free_fds(t_cmd *begin_cmd);
void	executor(char **argv, t_cmd *cmd, t_env *env);
void	init_pipe(t_cmd *cmd);
int		open_file(char *name, int i, int quit);
void	error(char *arg, int i, t_cmd *cmd, t_env *envm);
int		find_path_env(t_env *envm);

//tester
void	ft_print_tkn(t_tkn *tkn_begin);
void	ft_print_file2(t_file *file_begin);
void	ft_print_cmd(t_cmd *cmd);
void	ft_printtab(char **cmds);

#endif
