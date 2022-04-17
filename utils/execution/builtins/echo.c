/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:46:31 by roudouch          #+#    #+#             */
/*   Updated: 2022/04/12 17:48:52 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static int	check_echo_param(char *str)
{
	int	x;

	x = 0;
	while (str[x] != '\0')
	{
		if (str[x] != 'n')
			return (0);
		x++;
	}
	return (1);
}

static int	check_params(t_parm_lst *cmd, int *x,
		int *reading_echo_params, int *new_line)
{
	if (ft_strnstr(cmd->content[*x], "-n", 2)
		&& check_echo_param(cmd->content[*x] + 2)
		&& *reading_echo_params)
	{
		*new_line = 0;
		(*x)++;
		return (1);
	}
	return (0);
}

void	echo(t_parm_lst *cmd)
{
	int		x;
	int		reading_echo_params;
	int		new_line;

	x = 1;
	new_line = 1;
	reading_echo_params = 1;
	while (cmd->content[x])
	{
		if (check_params(cmd, &x, &reading_echo_params, &new_line))
			continue ;
		reading_echo_params = 0;
		write(1, cmd->content[x], ft_strlen(cmd->content[x]));
		x++;
		if (cmd->content[x])
			write(1, " ", 1);
	}
	if (new_line)
		write(1, "\n", 1);
	g_vars.exit_status = 0;
}
