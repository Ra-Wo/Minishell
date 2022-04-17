/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_struct_to_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:13:26 by roudouch          #+#    #+#             */
/*   Updated: 2022/04/11 22:28:20 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*ft_path_title_data(char const *s1, char const *s2)
{
	unsigned int	s1_len;
	unsigned int	s2_len;
	unsigned int	i;
	char			*ptr;

	if (!s1)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr = (char *)malloc((s1_len + s2_len + 2) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s1_len-- != 0)
		ptr[i++] = *s1++;
	ptr[i++] = '=';
	while (s2_len-- != 0)
		ptr[i++] = *s2++;
	ptr[i] = '\0';
	return (ptr);
}

static int	struct_length(t_env *env)
{
	t_env	*cpy;
	int		length;

	length = 1;
	cpy = env;
	while (cpy)
	{
		length++;
		cpy = cpy->next;
	}
	return (length);
}

char	**env_struct_to_array(void)
{
	t_env	*cpy;
	char	**array;
	int		x;

	x = 0;
	array = malloc(sizeof(char *) * struct_length(g_vars.env));
	if (!array)
	{
		perror("ERROR");
		return (NULL);
	}
	cpy = g_vars.env;
	while (cpy)
	{
		array[x++] = ft_path_title_data(cpy->title, cpy->data);
		cpy = cpy->next;
	}
	array[x] = NULL;
	return (array);
}
