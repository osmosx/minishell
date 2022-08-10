/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:51:15 by nenvoy            #+#    #+#             */
/*   Updated: 2022/07/31 16:32:41 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler(int sig)
{
	if (sig == SIGINT)
		ctrl_c(sig);
	if (sig == SIGQUIT)
		ctrl_backslash(sig);
}

void	ctrl_c(int signal)
{
	(void)signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ctrl_d(char *line, t_env *envm)
{
	printf("exit\n");
	free(line);
	free(envm);
	exit(0);
}

void	ctrl_backslash(int signal)
{
	(void)signal;
	rl_free_line_state();
	rl_cleanup_after_signal();
	printf("^\\Quit: 3\n");
	g_error = 131;
}

void	newline(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_error = 130;
}
