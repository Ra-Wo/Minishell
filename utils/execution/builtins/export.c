/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 12:37:07 by roudouch          #+#    #+#             */
/*   Updated: 2022/04/14 22:47:33 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static int	check_valid_title(char *line)
{
	int	x;
	int	flag;

	x = 0;
	flag = 0;
	if (!ft_isalpha(line[0]) && !(line[0] == '_'))
		flag = 1;
	while (line[x] != '=' && line[x] != '\0')
	{
		if (!ft_isalnum(line[x]) && !(line[x] == '+' && line[x + 1] == '='))
		{
			flag = 1;
			break ;
		}
		x++;
	}
	if (flag == 1)
	{
		g_vars.exit_status = 1;
		return (printf("export: '%s': not a valid identifier\n", line), 1);
	}
	return (0);
}

void	add_to_env(char *title, char *data)
{
	t_env	*cpy;

	cpy = g_vars.env;
	while (cpy->next)
	{
		if (compare(cpy->next->title, title))
		{
			free(cpy->next->data);
			cpy->next->data = ft_strdup(data);
			free(title);
			free(data);
			return ;
		}
		cpy = cpy->next;
	}
	cpy->next = create_new_env_element(title, data);
}

void	append_to_env(char *title, char *data)
{
	t_env	*cpy;
	char	*backup;

	cpy = g_vars.env;
	while (cpy->next)
	{
		if (compare(cpy->next->title, title))
		{
			backup = cpy->next->data;
			cpy->next->data = ft_strjoin(cpy->next->data, data);
			free(backup);
			free(data);
			free(title);
			return ;
		}
		cpy = cpy->next;
	}
	cpy->next = create_new_env_element(ft_strdup(title), ft_strdup(data));
	free(data);
	free(title);
}

static void	export_all(t_parm_lst *cmd, int *i, char *title, char *data)
{
	if (check_valid_title(cmd->content[(*i)]) && (*i)++)
		return ;
	title = env_get_title(cmd->content[(*i)]);
	data = env_get_data(cmd->content[(*i)]);
	if (data == NULL || title == NULL)
	{
		if (data)
			free(data);
		if (title)
			free(title);
		return ;
	}
	if (data[0] == '=')
		append_to_env(ft_strdup(title), ft_strdup(data + 1));
	else
		add_to_env(ft_strdup(title), ft_strdup(data));
	free(title);
	free(data);
	(*i)++;
}

int	export(t_parm_lst *cmd, t_vars *vars)
{
	char	*title;
	char	*data;
	int		i;
	int		status;

	status = 0;
	title = NULL;
	data = NULL;
	if (g_vars.env)
	{
		i = 1;
		if ((vars->i == 0) && (cmd->next == NULL) && cmd->content[1])
		{
			while (cmd->content[i])
				export_all(cmd, &i, title, data);
			return (1);
		}
	}
	return (0);
}
