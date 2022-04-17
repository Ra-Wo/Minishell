/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:12:57 by roudouch          #+#    #+#             */
/*   Updated: 2022/04/03 11:32:26 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	pwd(t_parm_lst *cmd)
{
	char	path[2000];

	if (cmd->content[1])
	{
		write(1, "pwd: too many arguments\n", 24);
		return ;
	}
	getcwd(path, 2000);
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
	g_vars.exit_status = 0;
}
