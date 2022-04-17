/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 13:37:24 by roudouch          #+#    #+#             */
/*   Updated: 2022/04/14 22:30:22 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	read_then_write(char *delimiter, int *fd)
{
	char	*str;

	str = get_next_line(0);
	if (!str)
		return (1);
	str = replace_dollar_sign(str);
	if (compare(delimiter, str))
	{
		free(str);
		return (1);
	}
	write(fd[1], str, ft_strlen(str));
	write(fd[1], "\n", 1);
	free(str);
	return (0);
}

int	run_heredoc(t_parm_lst *cmd, int *i)
{
	int		fd[2];

	(*i)++;
	if (pipe(fd) == -1)
		return (perror("ERROR"), -1);
	while (1)
	{
		if (read_then_write(cmd->input_redirect[(*i)], fd) == 1)
			break ;
	}
	if (!cmd->input_redirect[(*i) + 1] && dup2(fd[0], 0) == -1)
		return (close(fd[1]), close(fd[0]), perror("ERROR"), -1);
	close(fd[1]);
	close(fd[0]);
	return (0);
}
