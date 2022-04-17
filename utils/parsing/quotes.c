/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roudouch <roudouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 17:31:42 by akremcht          #+#    #+#             */
/*   Updated: 2022/04/12 17:55:59 by roudouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	allocate(char const *s, char **list, int word_length, int index)
{
	char	*word;

	word = (char *)malloc(sizeof(char) * (word_length + 1));
	if (!word)
	{
		while (index >= 0)
			free(list[index--]);
		free(list);
		return (0);
	}
	cpy(word, (s - word_length), word_length);
	list[index++] = word;
	return (1);
}

static int	check_flag(char const *s, char *flag, int *word_length)
{
	if ((*s == '\'' || *s == '\"') && *flag == '\0')
		*flag = *s;
	else if (*s == *flag)
		*flag = '\0';
	(*word_length)++;
	return (1);
}

static int	create_word(char const *s, char c, char **list, int words)
{
	int		word_length;
	int		index;
	char	flag;

	index = 0;
	flag = '\0';
	while (*s != '\0')
	{
		word_length = -1;
		if (*s != c)
		{
			while (index != words && check_flag(s, &flag, &word_length))
			{
				if ((*s == c || *s == '\0') && flag == '\0')
				{
					if (!allocate(s, list, word_length, index++))
						return (0);
					break ;
				}
				s++;
			}
		}
		s++;
	}
	return (index);
}

static int	count_words(char const *str, char c)
{
	int	words;
	int	flag;

	flag = '\0';
	words = 0;
	while (*str)
	{
		if ((*str == '\'' || *str == '\"') && flag == '\0')
			flag = *str;
		else if (*str == flag)
			flag = '\0';
		if (*str != c && (*(str + 1) == c
				|| *(str + 1) == '\0') && flag == '\0')
			words++;
		str++;
	}
	return (words);
}

char	**quote_split(char const *s, char c)
{
	int		words;
	char	**list;
	int		index;

	if (s == 0)
		return (0);
	words = count_words(s, c);
	list = malloc(sizeof(char *) * (words + 1));
	if (!list)
		return (NULL);
	index = create_word(s, c, list, words);
	if (!list)
		return (NULL);
	list[index] = NULL;
	return (list);
}
