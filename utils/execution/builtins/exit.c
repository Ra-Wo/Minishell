/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 21:04:57 by roudouch          #+#    #+#             */
/*   Updated: 2022/04/15 12:47:52 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	check_exit_status(char *line)
{
	int	x;

	x = 0;
	while (line[x] != '\0')
	{
		if (!ft_isdigit(line[x]))
		{
			if ((line[x] == '-' && (line[x + 1] == '-' || line[x + 1] == '+'))
				|| (line[x] == '+' && (line[x + 1] == '-'
						|| line[x + 1] == '+')))
				return (printf("exit: '%s': numeric argument required\n",
						line), 1);
		}
		x++;
	}
	return (0);
}

static void	_free(t_parm_lst *cmd, t_vars *vars)
{
	(void)cmd;
	free_parms(&vars->lst);
	free(vars->input);
	free(vars);
}

int	exit_the_program(t_parm_lst *cmd, t_vars *vars)
{
	int	len;
	int	status;

	(void)vars;
	if (!cmd->content)
		return (1);
	len = 0;
	while (cmd->content[len])
	{
		if (len != 0 && check_exit_status(cmd->content[len]))
			return (1);
		len++;
	}
	if (len > 2)
		return (printf("exit: too many arguments\n"), -1);
	if (cmd->content[1])
		status = ft_atoi(cmd->content[1]);
	else
		status = 0;
	if (len == 2)
		return (_free(cmd, vars), exit(status), 1);
	_free(cmd, vars);
	exit(1);
	return (1);
}
