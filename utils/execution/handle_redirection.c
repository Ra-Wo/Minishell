/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 13:37:38 by roudouch          #+#    #+#             */
/*   Updated: 2022/04/14 15:04:02 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	redirect_input(t_parm_lst *cmd)
{
	int	i;

	i = -1;
	while (cmd->input_redirect[++i])
	{
		if (ft_strnstr(cmd->input_redirect[i], "<<", 2))
		{
			if (run_heredoc(cmd, &i) == -1)
				return (-1);
		}
		else if (ft_strnstr(cmd->input_redirect[i], "<", 1))
		{
			if (get_data_from_a_file(cmd, &i) == -1)
				return (-1);
		}
	}
	return (0);
}

int	ft_append(t_parm_lst *cmd, int *i)
{
	int	fd;

	(*i)++;
	fd = open(cmd->output_redirect[*i], O_RDWR | O_APPEND | O_CREAT, 0642);
	if (fd == -1)
	{
		perror("ERROR");
		return (-1);
	}
	else if (!ft_strnstr(cmd->output_redirect[(*i) + 1], ">>", 2))
	{
		if (dup2(fd, 1) == -1)
		{
			perror("ERROR");
			return (-1);
		}
	}
	close(fd);
	return (0);
}

int	ft_trunc(t_parm_lst *cmd, int *i)
{
	int	fd;

	(*i)++;
	fd = open(cmd->output_redirect[*i], O_RDWR | O_TRUNC | O_CREAT, 0642);
	if (fd == -1)
	{
		return (perror("ERROR"), -1);
	}
	else if (!ft_strnstr(cmd->output_redirect[(*i) + 1], ">", 1))
	{
		if (dup2(fd, 1) == -1)
		{
			return (perror("ERROR"), -1);
		}
	}
	close(fd);
	return (0);
}

int	redirect_output(t_parm_lst *cmd)
{
	int	i;

	i = -1;
	while (cmd->output_redirect[++i])
	{
		if (ft_strnstr(cmd->output_redirect[i], ">>", 2))
		{
			if (ft_append(cmd, &i) == -1)
				return (-1);
		}
		else if (ft_strnstr(cmd->output_redirect[i], ">", 1))
		{
			if (ft_trunc(cmd, &i) == -1)
				return (-1);
		}
	}
	return (0);
}

int	handle_redirection(t_parm_lst *cmd)
{
	g_vars.input_has_redirect = 0;
	g_vars.output_has_redirect = 0;
	if (cmd->input_redirect)
	{
		if (redirect_input(cmd) == -1)
			return (-1);
		else
			g_vars.input_has_redirect = 1;
	}
	if (cmd->output_redirect)
	{
		if (redirect_output(cmd) == -1)
			return (-1);
		else
			g_vars.output_has_redirect = 1;
	}
	return (0);
}
