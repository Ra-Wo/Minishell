/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollar_sign_heredoc.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:49:29 by roudouch          #+#    #+#             */
/*   Updated: 2022/04/13 21:02:16 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*find_target(char *str)
{
	t_env	*cpy;
	char	*s;
	char	*num;

	if (str != NULL)
	{
		if (ft_strnstr(str, "?", 1))
		{
			num = ft_itoa(g_vars.exit_status);
			s = ft_strjoin(num, str + 1);
			return (free(str), free(num), s);
		}
		cpy = g_vars.env;
		while (cpy)
		{
			if (compare(str, cpy->title))
				return (free(str), ft_strdup(cpy->data));
			cpy = cpy->next;
		}
		free(str);
	}
	return (ft_strdup(""));
}

static int	length_after_dollar(char *str, int start)
{
	int	end;

	end = start + 1;
	while ((str[end] != ' ') && (str[end] != '$')
		&& (str[end] != '\0') && (str[end] != '\"')
		&& (ft_isalnum(str[end]) || str[end] == '?'
			|| str[end] == '_' || str[end] == '*'))
			end++;
	return (end - (start + 1));
}

static char	*replace(char *str, int index_of_dollar)
{
	char	*before_after[2];
	char	*data;
	char	*new;
	char	*backup;

	before_after[0] = ft_substr(str, 0, index_of_dollar);
	if (!before_after[0])
		return (perror("ERROR"), NULL);
	data = find_target(ft_substr(str, index_of_dollar + 1,
				length_after_dollar(str, index_of_dollar)));
	before_after[1] = ft_substr(str, ((index_of_dollar + 1
					+ length_after_dollar(str, index_of_dollar))),
			(ft_strlen(str) - index_of_dollar) + ft_strlen(data));
	if (!before_after[1])
		return (free(before_after[0]), free(data), perror("ERROR"), NULL);
	new = ft_strjoin(before_after[0], data);
	backup = new;
	new = ft_strjoin(new, before_after[1]);
	free(str);
	str = new;
	free(backup);
	free(data);
	free(before_after[0]);
	free(before_after[1]);
	return (str);
}

static char	*search_for_dollar_sign(char *str)
{
	int	x;
	int	flag;

	flag = '\0';
	x = 0;
	while (str[x])
	{
		if ((str[x] == '\'' || str[x] == '\"') && flag == '\0')
			flag = str[x];
		else if (str[x] == flag)
			flag = '\0';
		if (str[x] == '$' && (flag == '\"' || flag == '\0')
			&& str[x + 1] != ' ' && str[x + 1] != '\0')
			str = replace(str, x);
		x++;
	}
	return (str);
}

char	*replace_dollar_sign(char *str)
{
	if (str != NULL)
	{
		return (search_for_dollar_sign(str));
	}
	return (NULL);
}
