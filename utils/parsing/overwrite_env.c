/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overwrite_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 16:03:56 by akremcht          #+#    #+#             */
/*   Updated: 2022/04/07 21:19:38 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	**pop_element(char **tab, int to_remove)
{
	int		len;
	int		i;
	int		x;
	char	**new_tab;

	len = arr_len(tab);
	new_tab = malloc(sizeof(char *) * len);
	if (!new_tab)
		return (tab);
	i = -1;
	x = 0;
	while (tab[++i])
		if (to_remove != i)
			new_tab[x++] = tab[i];
	new_tab[x] = NULL;
	return (free(tab[to_remove]), free(tab), new_tab);
}

static char	**add_element(char **tab, char *to_add, int index)
{
	int		len;
	int		i;
	int		x;
	char	**new_tab;

	len = arr_len(tab);
	new_tab = malloc(sizeof(char *) * (len + 2));
	if (!new_tab)
		return (tab);
	i = -1;
	x = 0;
	while (tab[++i])
	{
		if (index == i)
			new_tab[x++] = to_add;
		new_tab[x++] = tab[i];
	}
	new_tab[x] = NULL;
	return (free(tab), new_tab);
}

static char	*find_env_data(char *str)
{
	t_env	*env_data;

	env_data = g_vars.env;
	while (env_data)
	{
		if (ft_strnstr(str, "?", ft_strlen(str)))
			return (ft_strjoin(ft_itoa(g_vars.exit_status), str + 1));
		if (compare(str, env_data->title))
			return (ft_strdup(env_data->data));
		env_data = env_data->next;
	}
	return (NULL);
}

void	check_overwrite(char ***tab)
{
	int		i[3];
	char	*str;
	char	*found;
	char	**found_splitted;

	i[0] = -1;
	while ((*tab)[++i[0]])
	{
		str = ft_strnstr((*tab)[i[0]], "$", ft_strlen((*tab)[i[0]]));
		if (str)
		{
			found_splitted = ft_split((*tab)[i[0]], '$');
			if (!found_splitted)
				return (ft_putstr_fd("failed to allocate", 2));
			i[1] = -1;
			while (found_splitted[++i[1]])
			{
				found = find_env_data(found_splitted[i[1]]);
				if (found)
					*tab = add_element(*tab, found, i[0]++);
			}
			*tab = pop_element(*tab, i[0]--);
			arr_free(found_splitted);
		}
	}
}
