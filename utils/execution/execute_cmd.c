/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 11:19:15 by roudouch          #+#    #+#             */
/*   Updated: 2022/04/14 23:24:19 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	parent(t_parm_lst *cmd, t_vars *vars, t_exec_vars *exec_vars)
{
	g_vars.pid = exec_vars->pid;
	if (vars->last_fd_pipe)
		close(vars->last_fd_pipe);
	if (cmd->next)
	{
		vars->last_fd_pipe = vars->fd[0];
		close(vars->fd[1]);
	}
	else
	{
		close(vars->fd[0]);
		close(vars->fd[1]);
	}
	vars->i++;
}

int	child(t_exec_vars *exec_vars, t_parm_lst *cmd, t_vars *vars)
{
	handle_out_in_of_pipe(vars, cmd);
	check_builtins_from_child(cmd, vars);
	if (!cmd->content)
		exit(0);
	if (execve(exec_vars->path, cmd->content, env_struct_to_array()) == -1)
		return (f_exit(cmd, vars, exec_vars->path), -1);
	return (0);
}

int	execute_cmd(t_parm_lst *cmd, t_vars *vars)
{
	t_exec_vars	exec_vars;

	exec_vars.path = NULL;
	if (cmd->content != NULL)
		exec_vars.path = get_path_cmd(cmd->content[0]);
	add_path_to_env(exec_vars.path);
	if (handle_redirection(cmd) == -1)
		return (0);
	if (check_builtins(cmd, vars))
		return (close(vars->fd[0]), close(vars->fd[1]),
			free(exec_vars.path), -1);
	exec_vars.pid = fork();
	if (exec_vars.pid == -1)
		return (f_free(cmd, vars, exec_vars.path), -1);
	if (exec_vars.pid == 0)
		child(&exec_vars, cmd, vars);
	else
		parent(cmd, vars, &exec_vars);
	free(exec_vars.path);
	return (0);
}
