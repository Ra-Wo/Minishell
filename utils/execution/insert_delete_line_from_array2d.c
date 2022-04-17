/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_delete_line_from_array2d.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:48:42 by roudouch          #+#    #+#             */
/*   Updated: 2022/04/07 16:40:22 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**insert_line(char **str, char *str_to_insert, int where)
{
	int		num_of_lines;
	int		i[2];
	char	**new;

	num_of_lines = 0;
	while (str[num_of_lines])
		num_of_lines++;
	if (where > num_of_lines)
		where = num_of_lines;
	new = malloc(sizeof(char *) * (num_of_lines + 2));
	if (!new)
		return (NULL);
	i[0] = 0;
	i[1] = 0;
	while (i[0] < where)
		new[i[0]++] = ft_strdup(str[i[1]++]);
	new[i[0]++] = ft_strdup(str_to_insert);
	while (i[1] < (num_of_lines))
		new[i[0]++] = ft_strdup(str[i[1]++]);
	new[i[0]] = NULL;
	return (new);
}

char	**delete_line(char **str, int where)
{
	int		num_of_lines;
	int		i[2];
	char	**new;
	int		remove;

	num_of_lines = 0;
	while (str[num_of_lines])
		num_of_lines++;
	remove = 0;
	if (!(where >= num_of_lines || where < 0))
		remove = 1;
	new = malloc(sizeof(char *) * (num_of_lines + remove));
	if (!new)
		return (NULL);
	i[0] = 0;
	i[1] = 0;
	while (i[1] < (num_of_lines - remove))
	{
		if ((i[0] == where && remove) && i[0]++ >= 0)
			continue ;
		new[i[1]++] = ft_strdup(str[i[0]++]);
	}
	new[i[1]] = NULL;
	return (new);
}
