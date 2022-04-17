/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:39:57 by roudouch          #+#    #+#             */
/*   Updated: 2022/04/14 22:32:36 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*paths_from_env(void)
{
	t_env	*cpy;

	cpy = g_vars.env;
	while (cpy)
	{
		if (compare(cpy->title, "PATH"))
			return (cpy->data);
		cpy = cpy->next;
	}
	return (NULL);
}

char	*get_path_cmd(char *cmd)
{
	int		i;
	char	*path;
	char	**paths;

	if (!cmd)
		return (NULL);
	if (cmd[0] == '.' || cmd[0] == '/')
		return (ft_strdup(cmd));
	paths = ft_split(paths_from_env(), ':');
	if (!paths)
		return (ft_strdup(cmd));
	i = 0;
	while (paths[i])
	{
		path = ft_pathjoin(paths[i], cmd);
		if (access(path, F_OK) != -1)
		{
			return (arr_free(paths), path);
		}
		free(path);
		i++;
	}
	arr_free(paths);
	return (ft_strdup(cmd));
}
