#ifndef MINISHELL_H
#define MINISHELL_H

#define CLOSE "\033[0m"                 // Закрыть все свойства
#define BLOD  "\033[1m"                 // Подчеркнуть, жирным шрифтом, выделить
#define BEGIN(x,y) "\033["#x";"#y"m"    // x: background, y: foreground

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
//# include <readline/readline.h>
//# include <readline/history.h>

# include "/Users/nenvoy/.brew/Cellar/\
readline/8.1.2/include/readline/readline.h"
# include "/Users/nenvoy/.brew/Cellar/\
readline/8.1.2/include/readline/history.h"

typedef struct s_env
{
	char **cp_env;
	char **cp_path;
}			   t_env;
// env utils
t_env	*init_env(void);
char	**copy_env(char **envp);

// signal utils
void	ctrl_c(int signal);

//built-in functions
void	m_env(t_env *envm);
int		m_pwd(void);

#endif
