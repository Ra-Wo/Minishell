/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 13:48:42 by roudouch          #+#    #+#             */
/*   Updated: 2022/04/13 15:00:57 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	compare(char *str1, char *str2)
{
	int	x;

	if (!str1 || !str2)
		return (0);
	x = 0;
	while (str2[x] || str1[x])
	{
		if (str1[x] != str2[x])
			return (0);
		x++;
	}
	return (1);
}
