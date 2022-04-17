/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akremcht <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 20:00:18 by akremcht          #+#    #+#             */
/*   Updated: 2022/03/14 15:43:42 by akremcht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	next_quote_pos(char const *str, int start, char q)
{
	int	i;

	start++;
	if (q == 39 || q == 34)
	{
		i = start;
		while (str[i])
		{
			if (str[i] == q)
				return (i);
			i++;
		}
	}
	return (start);
}

static int	wordslen(char const *s, char c)
{
	int	i;
	int	wdslen;

	i = 0;
	wdslen = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			wdslen++;
			while (s[i] && s[i] != c)
				i = next_quote_pos(s, i, s[i]);
		}
		else
			i++;
	}
	return (wdslen);
}

static int	check_for_splits(char const *s, char c, char **arr)
{
	int		i;
	int		arrlen;
	int		last;

	i = 0;
	arrlen = 0;
	last = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			last = i;
			while (s[i] && s[i] != c)
				i = next_quote_pos(s, i, s[i]);
			arr[arrlen] = malloc(i - last + 1);
			if (!arr[arrlen])
				return (0);
			ft_strlcpy(arr[arrlen++], s + last, i - last + 1);
		}
		else
			i++;
	}
	arr[arrlen] = 0;
	return (1);
}

char	**custom_split(char const *s, char c)
{
	char	**arr;
	int		i;

	if (!s)
		return (NULL);
	arr = (char **)malloc(sizeof(char *) * (wordslen(s, c) + 1));
	if (!arr)
		return (NULL);
	if (!check_for_splits(s, c, arr))
	{
		i = -1;
		while (arr[++i])
			free(arr[i]);
		free(arr);
		return (NULL);
	}
	return (arr);
}
