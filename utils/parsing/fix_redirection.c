/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 17:04:54 by roudouch          #+#    #+#             */
/*   Updated: 2022/04/12 17:55:32 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*redirection1(char *parm, int *i, char *backup, char **before_after)
{
	char	*new;

	(void)backup;
	before_after[0] = (ft_substr(parm, 0, *i));
	before_after[1] = (ft_substr(parm,
				(*i + ft_strlen(before_after[2])), ft_strlen(parm)));
	if ((*i) != 0)
		new = ft_strjoin(before_after[0], " ");
	else
		new = ft_strdup(before_after[0]);
	new = free_strjoin(new, before_after[2]);
	if (before_after[1][0] != '\0')
		new = free_strjoin(new, " ");
	new = free_strjoin(new, before_after[1]);
	(*i) += ft_strlen(before_after[2]);
	return (new);
}

static void	_free(char **before_after)
{
	if (before_after[0])
		free(before_after[0]);
	if (before_after[1])
		free(before_after[1]);
	if (before_after[2])
		free(before_after[2]);
}

char	*check_is_there_redirection(char *parm, int *i, char **before_after)
{
	char	*backup;
	char	*new;

	backup = NULL;
	new = NULL;
	before_after[2] = NULL;
	if (parm[(*i)] == '<' && parm[(*i) + 1] != '<' && parm[(*i) - 1] != '<')
		before_after[2] = ft_strdup("<");
	if (parm[(*i)] == '>' && parm[(*i) + 1] != '>')
		before_after[2] = ft_strdup(">");
	if (parm[(*i)] == '>' && parm[(*i) + 1] == '>')
		before_after[2] = ft_strdup(">>");
	if (parm[(*i)] == '<' && parm[(*i) + 1] == '<')
		before_after[2] = ft_strdup("<<");
	if (before_after[2] != NULL)
		new = redirection1(parm, i, backup, before_after);
	if (!new)
		return (ft_strdup(parm));
	return (_free(before_after), new);
}

int	is_redirection(char *parm)
{
	return (ft_strnstr(parm, ">", ft_strlen(parm))
		|| ft_strnstr(parm, "<", ft_strlen(parm))
		|| ft_strnstr(parm, ">>", ft_strlen(parm))
		|| ft_strnstr(parm, "<<", ft_strlen(parm)));
}

void	fix_redirection(char **parm)
{
	int		x;
	int		i;
	char	*backup;
	char	*before_after[4];

	if (!parm)
		return ;
	x = 0;
	while (parm[x])
	{
		i = 0;
		while (is_redirection(parm[x]) && parm[x][i])
		{
			before_after[0] = NULL;
			before_after[1] = NULL;
			before_after[2] = NULL;
			backup = parm[x];
			parm[x] = check_is_there_redirection(parm[x], &i, before_after);
			free(backup);
			i++;
		}
		x++;
	}
}
