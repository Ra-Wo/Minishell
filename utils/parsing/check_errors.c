/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:23:21 by akremcht          #+#    #+#             */
/*   Updated: 2022/04/08 22:32:34 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_quotes(char *str)
{
	int		x;
	int		flag;
	int		quotes;

	x = -1;
	quotes = 0;
	flag = '\0';
	while (str[++x])
	{
		if ((str[x] == '\'' || str[x] == '\"') && flag == '\0')
		{
			quotes++;
			flag = str[x];
		}
		else if (str[x] == flag && quotes++)
			flag = '\0';
	}
	if ((quotes % 2) != 0)
	{
		ft_putstr_fd("Error: unclosed quote ", 2);
		return (write(2, &flag, 1), ft_putstr_fd("\n", 2), 1);
	}
	return (0);
}

void	cpy(char *dst, char const *src, int n)
{
	char	flag;

	flag = '\0';
	while (n--)
	{
		if ((*src == '\'' || *src == '\"') && flag == '\0')
		{
			flag = *src;
			src++;
			continue ;
		}
		else if (*src == flag)
		{
			flag = '\0';
			src++;
			continue ;
		}
		*dst++ = *src++;
	}
	*dst = '\0';
}
