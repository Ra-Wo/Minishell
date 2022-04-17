/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 11:45:25 by roudouch          #+#    #+#             */
/*   Updated: 2022/04/15 11:46:37 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	free_replace_dollar(t_replace_dollar *replace, int free_backup)
{
	free(replace->before);
	free(replace->after);
	free(replace->data);
	if (free_backup)
		free(replace->backup);
}
