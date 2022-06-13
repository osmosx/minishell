/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nenvoy <nenvoy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:55:27 by nenvoy            #+#    #+#             */
/*   Updated: 2022/04/26 15:55:31 by nenvoy           ###   ########.fr       */
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

//Для дома
//# include "/usr/local/Cellar/readline/8.1.2/include/readline/readline.h"
//# include "/usr/local/Cellar/readline/8.1.2/include/readline/history.h"

//Вариант для Brew
//# include "/Users/nenvoy/.brew/Cellar/readline/8.1.2/include/readline/readline.h"
//# include "/Users/nenvoy/.brew/Cellar/readline/8.1.2/include/readline/history.h"

int	g_error;
int	g_status;

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
	t_file			*begin_redirs;
	struct s_cmd	*next;
//	t_tkn	*prev;
}				t_cmd;

// env utils
t_env	*init_env(t_env *envm, char **envp);
char	**copy_env(t_env *envm, char **env);
char	**unset_remove(t_env *envm, char *cmd);

// signal utils
void	ctrl_c(int signal);
void	ctrl_d(char *line, t_env *envm);

//built-in functions
int		m_pwd(void);
void	m_env(t_env *envm);
void	m_echo(char **cmd2);
void	m_exit(t_env *envm);
void	m_unset(t_env *envm, char **cmd2);
void	m_cd(t_env *envm, char *path);
t_env	*m_export(t_env	*envm, char **cmd2);
//export utils
void	change_line_value(char **tab, char *new_str, int i);
int		find_line_in_tab(char **env, char *arg);
char	**add_line(char **arr, char *new_line);
char	**del_line(char **arr, int pos);
char	**con_twotab(char **tab, char **tab2);

//parser utils
char	**ft_pipe_separator(char *str);

//utils
char	**ft_free(char **arr);
char	**add_line(char **arr, char *new_line);
int		tablen(char **tab);
int		check_export_arg(char *cmd);

#endif
