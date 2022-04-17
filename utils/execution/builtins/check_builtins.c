/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:50:12 by roudouch          #+#    #+#             */
/*   Updated: 2022/04/15 12:34:12 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static char	*to_lowercase(char *str)
{
	int	x;

	x = 0;
	while (str[x] != '\0')
	{
		str[x] = ft_tolower(str[x]);
		x++;
	}
	return (str);
}

int	check_builtins_from_child(t_parm_lst *cmd, t_vars *vars)
{
	if (!cmd->content || !cmd->content[0])
		return (0);
	(void)vars;
	if (compare(to_lowercase(cmd->content[0]), "env"))
		return (env(), exit(0), 0);
	if (compare((cmd->content[0]), "export") && !cmd->content[1])
		return (print_export(), exit(0), 0);
	if (compare(to_lowercase(cmd->content[0]), "echo"))
		return (echo(cmd), exit(0), 0);
	if (compare(to_lowercase(cmd->content[0]), "pwd"))
		return (pwd(cmd), exit(0), 0);
	return (0);
}

int	check_builtins(t_parm_lst *cmd, t_vars *vars)
{
	if (!cmd->content || !cmd->content[0])
		return (0);
	if (compare((cmd->content[0]), "exit") && !cmd->next)
		return (printf("exit\n"), exit_the_program(cmd, vars));
	if (compare((cmd->content[0]), "export"))
		return (export(cmd, vars));
	if (compare(to_lowercase(cmd->content[0]), "cd"))
		return (cd(cmd), (1));
	if (compare((cmd->content[0]), "unset"))
		return (unset(cmd), (1));
	return (0);
}
