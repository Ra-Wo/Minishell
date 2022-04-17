/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:44:34 by roudouch          #+#    #+#             */
/*   Updated: 2022/04/14 22:29:14 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_data_from_a_file(t_parm_lst *cmd, int *i)
{
	int	fd;

	(*i)++;
	fd = open(cmd->input_redirect[(*i)], O_RDONLY);
	if (fd == -1)
	{
		perror("ERROR");
		return (-1);
	}
	else if (!cmd->input_redirect[(*i) + 1])
	{
		if (dup2(fd, 0) == -1)
		{
			perror("ERROR");
			return (close(fd), -1);
		}
	}
	close(fd);
	return (0);
}
