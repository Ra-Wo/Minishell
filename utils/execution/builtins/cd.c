/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:50:58 by roudouch          #+#    #+#             */
/*   Updated: 2022/04/14 14:30:17 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	change_path_in_env(t_env *env, char *old_path)
{
	char	*path;
	t_env	*cpy;

	path = malloc(sizeof(char) * 2000);
	if (!old_path)
		return (perror("ERROR"), 0);
	getcwd(path, 2000);
	cpy = env;
	while (cpy->next)
	{
		if (compare(cpy->next->title, "OLDPWD"))
		{
			free(cpy->next->data);
			cpy->next->data = ft_strdup(old_path);
		}
		if (compare(cpy->next->title, "PWD"))
		{
			free(cpy->next->data);
			cpy->next->data = ft_strdup(path);
		}
		cpy = cpy->next;
	}
	free(path);
	return (0);
}

// remove line 54
int	cd(t_parm_lst *cmd)
{
	char	*old_path;

	old_path = malloc(sizeof(char) * 2000);
	if (!old_path)
		return (perror("ERROR"), 0);
	getcwd(old_path, 2000);
	if (ft_strnstr(cmd->content[1], "~", 4) || !cmd->content[1])
	{
		if (chdir(getenv("HOME")) != 0)
		{
			perror("ERROR");
			g_vars.exit_status = 1;
		}
		return (free(old_path), 0);
	}
	if (chdir(cmd->content[1]) != 0)
	{
		perror("ERROR");
		g_vars.exit_status = 1;
		return (free(old_path), 0);
	}
	g_vars.exit_status = 0;
	return (change_path_in_env(g_vars.env, old_path), free(old_path), 0);
}
