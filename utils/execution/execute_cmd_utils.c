/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:19:18 by roudouch          #+#    #+#             */
/*   Updated: 2022/04/14 14:07:20 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_path_to_env(char *str)
{
	t_env	*cpy;
	int		i;

	if (!str)
		return ;
	i = 1;
	cpy = g_vars.env;
	while (cpy)
	{
		if (compare("_", cpy->title))
		{
			i = 0;
			free(cpy->data);
			cpy->data = ft_strdup(str);
		}
		cpy = cpy->next;
	}
	if (i)
	{
		add_to_env(ft_strdup("_"), ft_strdup(str));
	}
}

void	f_free(t_parm_lst *cmd, t_vars *vars, char *path)
{
	if (cmd)
		free_parms(&cmd);
	if (path)
		free(path);
	if (vars->input)
		free(vars->input);
	if (vars)
		free(vars);
}

int	check_if_not_path(char *str)
{
	int	x;

	x = 0;
	while (str[x])
	{
		if (ft_isalpha(str[x++]))
			return (0);
	}
	return (1);
}

void	f_exit(t_parm_lst *cmd, t_vars *vars, char *path)
{
	int	s_exit;

	s_exit = 0;
	if (ft_strnstr(cmd->content[0], ".", 1)
		&& cmd->content[0][1] == '\0' && !cmd->content[1])
		s_exit = 2;
	else if ((ft_strnstr(cmd->content[0], "./", 2)
			|| ft_strnstr(cmd->content[0], "/", 1))
		&& check_if_not_path(cmd->content[0]))
		s_exit = 126;
	else
		s_exit = 127;
	if (s_exit == 127)
		printf("ERROR: %s: command not found\n", cmd->content[0]);
	else if (s_exit == 126)
	{	
		write(1, "ERROR: ", 7);
		write(1, cmd->content[0], ft_strlen(cmd->content[0]));
		write(1, " is a directory\n", 16);
	}
	else
		write(1, "ERROR: No such file or directory\n", 33);
	f_free(cmd, vars, path);
	exit(s_exit);
}
