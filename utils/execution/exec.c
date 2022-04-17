/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 16:49:41 by roudouch          #+#    #+#             */
/*   Updated: 2022/04/14 22:55:35 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_exit_status_var(int status)
{	
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 9)
			g_vars.exit_status = 1;
		else if (WTERMSIG(status) == 2)
		{
			write(1, "\n", 1);
			g_vars.exit_status = 130;
		}
		else if (WTERMSIG(status) == 3)
		{
			write(1, "Quit: 3\n", 8);
			g_vars.exit_status = 131;
		}
		else
			g_vars.exit_status = WTERMSIG(status);
	}
	else
		g_vars.exit_status = WEXITSTATUS(status);
}

int	c_exec(t_vars *vars, t_parm_lst	*cpy)
{
	signal(SIGQUIT, ctrl_backslash);
	signal(SIGINT, ctrl_c_when_cmd_is_running);
	g_vars.old_fd[0] = dup(0);
	g_vars.old_fd[1] = dup(1);
	if (pipe(vars->fd) == -1)
		return (perror("ERROR: "), 0);
	execute_cmd(cpy, vars);
	return (1);
}

static int	return_the_old_fd(void)
{
	if (g_vars.old_fd[0] != -1)
	{
		if (dup2(g_vars.old_fd[0], 0) == -1)
			return (perror("ERROR"), 1);
	}
	if (g_vars.old_fd[1] != -1)
	{
		if (dup2(g_vars.old_fd[1], 1) == -1)
			return (perror("ERROR"), 1);
	}
	return (0);
}

int	exec(t_parm_lst *lst, t_vars *vars)
{
	int			exit_status_child;
	t_parm_lst	*cpy;

	cpy = lst;
	while (cpy)
	{
		if (c_exec(vars, cpy) == 0)
			return (0);
		if (return_the_old_fd())
			return (0);
		cpy = cpy->next;
	}
	exit_status_child = -1;
	while (wait(&exit_status_child) > 0)
		;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl_c);
	if (exit_status_child != -1)
		check_exit_status_var(exit_status_child);
	return (0);
}
