/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzimmerm <hzimmerm@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:20:42 by hzimmerm          #+#    #+#             */
/*   Updated: 2025/01/26 20:23:08 by hzimmerm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' \
		|| c == '\r' || c == '\f' || c == '\v')
		return (1);
	return (0);
}

static int	ft_count_words(char const *s)
{
	int	is_word;
	int	i;
	int	count;

	i = 0;
	is_word = 0;
	count = 0;
	while (s[i] != 0)
	{
		if (!is_whitespace(s[i]))
			is_word = 1;
		if (is_whitespace(s[i]) && is_word == 1)
		{
			count++;
			is_word = 0;
		}
		i++;
	}
	if (s[i] == 0 && is_word == 1)
		count++;
	return (count);
}

static char	*ft_strdup_c(const char *s)
{
	char	*dup;
	int		i;
	int		length;

	length = 0;
	i = 0;
	while (s[length] != 0 && !is_whitespace(s[length]))
		length++;
	dup = (char *)malloc(sizeof(char) * (length + 1));
	if (dup == 0)
		return (0);
	while (i < length)
	{
		dup[i] = s[i];
		i++;
	}
	dup[length] = 0;
	return (dup);
}

static void	*ft_loop_outs(char **array, char const *s, int count)
{
	int	j;
	int	i;	

	j = 0;
	i = 0;
	while (i < count)
	{
		while (is_whitespace(s[j]))
			j++;
		array[i] = ft_strdup_c(&s[j]);
		if (array[i] == 0)
		{
			while (i >= 0)
				free(array[i--]);
			free(array);
			return (0);
		}
		while (s[j] != '\0' && !is_whitespace(s[j]))
			j++;
		i++;
	}
	return ((void *)1);
}

char	**ft_split_space(char const *s)
{
	char	**array;
	int		count;

	if (s == 0)
		return (0);
	count = ft_count_words(s);
	array = (char **)malloc((count + 1) * sizeof(char *));
	if (!array)
		return (0);
	if (ft_loop_outs(array, s, count) == NULL)
		return (0);
	array[count] = 0;
	return (array);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char string[] = "lorem ipsum dolor sit amet, consectetur adipiscing elit";
// 	char c = 't';
// 	char **array;
// 	int	i;
// 	i = 0;
// 	array = ft_split(string, c);
// 	while (array[i] != 0)
// 	{
// 		printf("%s\n", array[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (array[i] != 0)
// 	{
// 		free(array[i]);
// 		i++;
// 	}
// 	free(array);
// 	return (0);
// }
