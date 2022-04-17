/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 16:17:16 by roudouch          #+#    #+#             */
/*   Updated: 2022/04/14 22:52:31 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(t_vars *vars, char **env)
{
	(void)vars;
	g_vars.exit_status = 0;
	create_env(env);
}

void	ctrl_backslash(int s)
{
	(void)s;
	g_vars.exit_status = 131;
}

void	ctrl_c_when_cmd_is_running(int s)
{
	(void)s;
	g_vars.exit_status = 130;
}

void	ctrl_c(int s)
{
	(void)s;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_vars.exit_status = 1;
}

int	main(int ac, char **av, char **env)
{
	t_vars	vars;

	(void)ac;
	(void)av;
	init(&vars, env);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl_c);
	reading_input(&vars);
	return (0);
}
