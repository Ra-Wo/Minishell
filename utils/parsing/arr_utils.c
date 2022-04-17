/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 23:34:23 by akremcht          #+#    #+#             */
/*   Updated: 2022/04/12 17:55:03 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_all_redirection(char *parm)
{
	return (!ft_strncmp(parm, ">", 1) || !ft_strncmp(parm, "<", 1)
		|| !ft_strncmp(parm, ">>", 2) || !ft_strncmp(parm, "<<", 2));
}

int	all_redirections_len(char **parms)
{
	int		i;
	int		len;
	int		is_red;

	if (!parms)
		return (1);
	i = -1;
	len = 0;
	while (parms[++i])
	{
		is_red = is_all_redirection(parms[i]);
		if (is_red && !parms[i + 1])
			return (-1);
		if (is_red && parms[i + 1])
		{
			if (is_all_redirection(parms[i + 1]))
				return (-1);
			i++;
			len += 2;
		}
	}
	return (len);
}

int	arr_len(char **arr)
{
	int	len;

	if (!arr)
		return (0);
	len = 0;
	while (arr[len])
		len++;
	return (len);
}

void	arr_free(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_parms(t_parm_lst **lst)
{
	t_parm_lst	*next_cpy;

	if (!lst)
		return ;
	while (*lst)
	{
		next_cpy = (*lst)->next;
		arr_free((*lst)->content);
		arr_free((*lst)->output_redirect);
		arr_free((*lst)->input_redirect);
		free(*lst);
		*lst = next_cpy;
	}
}
