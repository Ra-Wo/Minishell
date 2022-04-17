/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_out_in_of_pipe.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:13:15 by roudouch          #+#    #+#             */
/*   Updated: 2022/04/14 23:08:07 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	for_first_cmd(t_vars *vars)
{
	if (g_vars.output_has_redirect != 1 && dup2(vars->fd[1], 1) == -1)
	{
		perror("ERROR");
		exit(1);
	}
}

static void	for_middle_cmd(t_vars *vars)
{
	if (g_vars.input_has_redirect != 1 && dup2(vars->last_fd_pipe, 0) == -1)
	{
		perror("ERROR");
		exit(1);
	}
	if (dup2(vars->fd[1], 1) == -1)
	{
		perror("ERROR");
		exit(1);
	}
}

static void	for_last_cmd(t_vars *vars)
{
	if (g_vars.input_has_redirect != 1 && dup2(vars->last_fd_pipe, 0) == -1)
	{
		perror("ERROR");
		exit(1);
	}
}

void	handle_out_in_of_pipe(t_vars *vars, t_parm_lst *cmd)
{
	if (vars->i == 0 && cmd->next)
		for_first_cmd(vars);
	else if (vars->i != 0 && cmd->next)
		for_middle_cmd(vars);
	else if (vars->i != 0)
		for_last_cmd(vars);
	close(vars->fd[0]);
	close(vars->fd[1]);
	if (vars->i != 0)
		close(vars->last_fd_pipe);
}
