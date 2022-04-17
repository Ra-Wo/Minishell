/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 23:34:58 by akremcht          #+#    #+#             */
/*   Updated: 2022/04/11 11:30:51 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	r_len(char **parms, char *red)
{
	int		i;
	int		len;

	if (!parms)
		return (0);
	i = -1;
	len = 0;
	while (parms[++i])
	{
		if (compare(parms[i], red) && parms[i + 1])
		{
			len += 2;
			i++;
		}
	}
	return (len);
}

static int	get_r(char **p, int i, char ***to_add, int y)
{
	int	parm_len;
	int	len;

	parm_len = ft_strlen(p[i]);
	if (parm_len == 0)
		return (y);
	if (!(*to_add))
	{
		len = 0;
		if (compare(p[i], ">") || compare(p[i], ">>"))
			len = r_len(p, ">") + r_len(p, ">>");
		else if (compare(p[i], "<") || compare(p[i], "<<"))
			len = r_len(p, "<") + r_len(p, "<<");
		*to_add = malloc(sizeof(char *) * (len + 1));
		if (!(*to_add))
			return (-1);
	}
	(*to_add)[y] = p[i];
	(*to_add)[y + 1] = p[i + 1];
	(*to_add)[y + 2] = NULL;
	return (y + 2);
}

static int	get_redirections(t_parm_lst *lst, char **parms, int *num)
{
	while (parms[++num[0]])
	{
		if (!is_all_redirection(parms[num[0]]))
			continue ;
		if (compare(parms[num[0]], ">") || compare(parms[num[0]], ">>"))
			num[1] = get_r(parms, num[0], &lst->output_redirect, num[1]);
		if (compare(parms[num[0]], "<") || compare(parms[num[0]], "<<"))
			num[2] = get_r(parms, num[0], &lst->input_redirect, num[2]);
		if (num[1] == -1 || num[2] == -1)
		{
			if (lst->output_redirect)
				free(lst->output_redirect);
			if (lst->input_redirect)
				free(lst->input_redirect);
			return (0);
		}
	}
	return (1);
}

static char	**get_new_parms(char **parms, int red_len)
{
	char		**new_parms;
	int			i;
	int			len;

	if (arr_len(parms) - red_len == 0)
		return (NULL);
	new_parms = malloc(sizeof(char *) * (arr_len(parms) - red_len + 1));
	if (!new_parms)
		return (NULL);
	i = -1;
	len = 0;
	while (parms[++i])
	{
		if (is_all_redirection(parms[i])
			&& parms[i + 1])
		{
			i++;
			continue ;
		}
		new_parms[len++] = parms[i];
	}
	new_parms[len] = NULL;
	return (new_parms);
}

t_parm_lst	*check_redirections(char **parms)
{
	t_parm_lst	*lst;
	int			red_len;
	char		**new_parms;
	int			num[3];

	if (!parms)
		return (NULL);
	red_len = all_redirections_len(parms);
	if (red_len == 0)
		return (ft_lstnew(parms));
	if (red_len == -1)
		return (ft_putstr_fd("Syntax error: near unexpected token\n", 2), NULL);
	new_parms = get_new_parms(parms, red_len);
	lst = ft_lstnew(new_parms);
	if (!lst)
		return (free(parms), free(new_parms), NULL);
	num[0] = -1;
	num[1] = 0;
	num[2] = 0;
	if (!get_redirections(lst, parms, num))
		return (free(lst), free(parms), free(new_parms), NULL);
	return (free(parms), lst);
}
