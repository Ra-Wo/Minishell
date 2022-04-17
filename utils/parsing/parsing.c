/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 15:19:04 by roudouch          #+#    #+#             */
/*   Updated: 2022/04/15 11:01:59 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_parm_lst	*get_parms(char *input, int i)
{
	char		**splitted;
	char		**parm_lst;
	t_parm_lst	*lst;
	t_parm_lst	*new;

	splitted = custom_split(input, '|');
	if (!splitted)
		return (NULL);
	i = -1;
	lst = NULL;
	while (splitted[++i])
	{
		fix_redirection(splitted);
		parm_lst = quote_split(splitted[i], ' ');
		free(splitted[i]);
		if (!parm_lst)
			return (free(splitted), free_parms(&lst), NULL);
		new = check_redirections(parm_lst);
		if (!new)
			return (free(splitted), arr_free(parm_lst), free_parms(&lst), NULL);
		ft_lstadd_back(&lst, new);
	}
	return (free(splitted), lst);
}

static int	check_spaces(char *str)
{
	int	x;

	x = 0;
	while (str[x] == ' ')
		x++;
	if (str[x] == '\0')
		return (1);
	return (0);
}

static int	check_pipe(char *str)
{
	int		x;
	int		found;

	x = -1;
	found = 0;
	while (str[x + 1] == ' ')
		x++;
	if (str[x + 1] == '|')
		x = -2;
	while (x != -2 && str[++x])
	{
		if (str[x] == '|')
			found = 1;
		else if (str[x] != ' ')
			found = 0;
	}
	if (x == -2 || found)
	{
		ft_putstr_fd("Error: syntax error near unexpected token ", 2);
		return (write(2, "|", 1), ft_putstr_fd("\n", 2), 1);
	}
	return (0);
}

void	reading_input(t_vars *vars)
{
	t_parm_lst	*lst;
	int			i;

	i = 0;
	while (1)
	{
		vars = malloc(sizeof(t_vars));
		vars->i = 0;
		vars->last_fd_pipe = 0;
		vars->input = readline("MINISHELL$: ");
		add_history(vars->input);
		replace_all_dollar_sign(vars);
		if (check_exit(vars) && !check_spaces(vars->input)
			&& !check_pipe(vars->input) && !check_quotes(vars->input))
		{
			lst = get_parms(vars->input, i);
			vars->lst = lst;
			exec(lst, vars);
			free_parms(&lst);
		}
		free(vars->input);
		free(vars);
	}
}
