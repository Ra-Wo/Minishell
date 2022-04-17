/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:31:25 by roudouch          #+#    #+#             */
/*   Updated: 2022/04/15 11:45:51 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

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

static int	length_after_dollar(t_vars *vars, int start)
{
	int	end;

	end = start + 1;
	while ((vars->input[end] != ' ') && (vars->input[end] != '$')
		&& (vars->input[end] != '\0') && (vars->input[end] != '\"')
		&& (ft_isalnum(vars->input[end]) || vars->input[end] == '?'
			|| vars->input[end] == '_' || vars->input[end] == '*'))
		end++;
	return (end - (start + 1));
}

static int	replace(t_vars *vars, int index_of_dollar)
{
	t_replace_dollar	rd;

	rd.before = ft_substr(vars->input, 0, index_of_dollar);
	if (!rd.before)
		return (perror("ERROR"), -1);
	rd.data = find_target(ft_substr(vars->input, index_of_dollar
				+ 1, length_after_dollar(vars, index_of_dollar)));
	if (!rd.data)
		return (free(rd.before), perror("ERROR"), -1);
	rd.after = ft_substr(vars->input, ((index_of_dollar + 1
					+ length_after_dollar(vars, index_of_dollar))),
			(ft_strlen(vars->input) - index_of_dollar) + ft_strlen(rd.data));
	if (!rd.after)
		return (free(rd.before), free(rd.data), perror("ERROR"), -1);
	rd.new = ft_strjoin(rd.before, rd.data);
	if (!rd.new)
		return (free_replace_dollar(&rd, 0), perror("ERROR"), -1);
	rd.backup = rd.new;
	rd.new = ft_strjoin(rd.new, rd.after);
	if (!rd.new)
		return (free(rd.before), free(rd.data), free(rd.after),
			perror("ERROR"), -1);
	free(vars->input);
	vars->input = rd.new;
	return (free_replace_dollar(&rd, 1), 1);
}

static void	search_for_dollar_sign(t_vars *vars)
{
	int	x;
	int	flag;

	flag = '\0';
	x = 0;
	while (vars->input[x])
	{
		if ((vars->input[x] == '\'' || vars->input[x] == '\"') && flag == '\0')
			flag = vars->input[x];
		else if (vars->input[x] == flag)
			flag = '\0';
		if (vars->input[x] == '$' && (flag == '\"' || flag == '\0')
			&& vars->input[x + 1] != ' ' && vars->input[x + 1] != '\0')
			replace(vars, x);
		x++;
	}
}

int	replace_all_dollar_sign(t_vars *vars)
{
	if (vars->input)
	{
		search_for_dollar_sign(vars);
	}
	return (1);
}
