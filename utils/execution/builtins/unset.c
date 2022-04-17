/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:26:09 by roudouch          #+#    #+#             */
/*   Updated: 2022/04/14 22:46:37 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static int	check_valid(char *line)
{
	int	x;
	int	flag;

	x = 0;
	flag = 0;
	if (!ft_isalpha(line[0]) && !(line[0] == '_'))
		flag = 1;
	while (line[x] != '\0')
	{
		if (!ft_isalnum(line[x]))
		{
			flag = 1;
			break ;
		}
		x++;
	}
	if (flag == 1)
	{
		g_vars.exit_status = 1;
		return (printf("unset: '%s': not a valid identifier\n", line), 1);
	}
	return (0);
}

static void	remove_varible_from_env(t_parm_lst *cmd,
	int i, t_env *cpy, t_env *backup)
{
	while (cmd->content[i])
	{
		cpy = g_vars.env;
		while (cpy)
		{
			if (check_valid(cmd->content[i]))
				return ;
			if (compare(cpy->next->title, cmd->content[i]))
			{
				backup = cpy->next;
				if (cpy->next->next == NULL)
					cpy->next = NULL;
				else
					cpy->next = cpy->next->next;
				free(backup->data);
				free(backup->title);
				free(backup);
				break ;
			}
			cpy = cpy->next;
		}
		i++;
	}
}

void	unset(t_parm_lst *cmd)
{
	t_env	*cpy;
	t_env	*backup;
	int		i;

	cpy = NULL;
	backup = NULL;
	i = 1;
	if (g_vars.env)
		remove_varible_from_env(cmd, i, cpy, backup);
}
