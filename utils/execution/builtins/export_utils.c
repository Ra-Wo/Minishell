/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:31:08 by roudouch          #+#    #+#             */
/*   Updated: 2022/04/13 14:38:48 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_env	*create_new_env_element(char *title, char *data)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->title = ft_strdup(title);
	new->data = ft_strdup(data);
	new->next = NULL;
	free(title);
	free(data);
	return (new);
}

char	*env_get_title(char *line)
{
	int	x;

	x = 0;
	while (line[x] != '\0' && (line[x] != '=' && line[x] != '+'))
		x++;
	return (ft_substr(line, 0, x));
}

char	*env_get_data(char *line)
{
	int	x;

	x = 0;
	while (line[x] != '\0' && (line[x] != '=' && line[x] != '+'))
		x++;
	if ((ft_strlen(line) - x) == 0)
		return (ft_strdup("\0"));
	return (ft_substr(line, (x + 1), (ft_strlen(line) - x)));
}

void	print_export(void)
{
	t_env	*cpy;

	cpy = g_vars.env;
	while (cpy)
	{
		printf("declare -x %s=\"%s\"\n", cpy->title, cpy->data);
		cpy = cpy->next;
	}
}
