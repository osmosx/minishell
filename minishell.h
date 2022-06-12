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

// env utils
t_env	*init_env(t_env *envm, char **envp);
char	**copy_env(t_env *envm, char **env);

// signal utils
void	ctrl_c(int signal);

//built-in functions
int		m_pwd(void);
void	m_env(t_env *envm);
void	m_echo(char **cmd2);
void	m_exit(t_env *envm);
t_env	*m_export(t_env	*envm, char **cmd2);
void	m_unset(t_env *envm, char **cmd2);
void	m_cd(t_env *envm, char *path);

//parser utils
char	**ft_pipe_separator(char *str);

//utils
char	**ft_free(char **arr);
char	**add_line(char **arr, char *new_line);
int		tablen(char **tab);

#endif
