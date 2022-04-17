/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 12:09:47 by roudouch          #+#    #+#             */
/*   Updated: 2022/04/08 14:10:42 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	env(void)
{
	t_env	*cpy;

	cpy = g_vars.env;
	while (cpy)
	{
		if (cpy->data[0] != '\0')
			printf("%s=%s\n", cpy->title, cpy->data);
		cpy = cpy->next;
	}
}
