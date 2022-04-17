/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 11:50:55 by roudouch          #+#    #+#             */
/*   Updated: 2022/04/14 21:03:02 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_exit(t_vars *vars)
{
	int	x;

	x = 0;
	if (!vars->input)
	{
		if (vars->input)
			free(vars->input);
		if (g_vars.env)
			free_env();
		exit(0);
	}
	return (1);
}
