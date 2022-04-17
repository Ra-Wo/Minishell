/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:08:26 by roudouch          #+#    #+#             */
/*   Updated: 2022/04/14 00:04:46 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*_env_get_title(char *line)
{
	int	x;

	x = 0;
	while (line[x] != '=')
		x++;
	return (ft_substr(line, 0, x));
}

static char	*_env_get_data(char *line)
{
	int	x;

	x = 0;
	while (line[x] != '=')
		x++;
	x += 1;
	return (ft_substr(line, x, (ft_strlen(line) - x)));
}

void	free_env(void)
{
	t_env	*cpy;
	t_env	*backup;

	cpy = g_vars.env;
	while (cpy)
	{
		free(cpy->title);
		free(cpy->data);
		backup = cpy;
		cpy = cpy->next;
		free(backup);
	}
}

void	create_env_countinue(char **env, int *x, t_env *last)
{
	t_env	*block;
	char	*backup;

	while (env[(*x)])
	{
		block = malloc(sizeof(t_env));
		block->title = _env_get_title(env[(*x)]);
		backup = _env_get_data(env[(*x)]);
		if (compare(block->title, "SHLVL"))
		{
			block->data = ft_itoa((ft_atoi(backup) + 1));
			free(backup);
		}
		else
			block->data = backup;
		if ((*x) == 0)
			g_vars.env = block;
		else
			last->next = block;
		last = block;
		(*x)++;
	}
	last->next = NULL;
}

void	create_env(char **env)
{
	int		x;
	t_env	*last;

	last = NULL;
	x = 0;
	if (*env)
	{
		create_env_countinue(env, &x, last);
	}
	else
	{
		g_vars.env = malloc(sizeof(t_env));
		g_vars.env->title = ft_strdup("SHLVL");
		g_vars.env->data = ft_strdup("1");
		g_vars.env->next = NULL;
	}
}
