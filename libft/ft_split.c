/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:13:19 by gojeda            #+#    #+#             */
/*   Updated: 2025/04/11 14:13:20 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*ft_save_word(const char **s, char c)
{
	const char	*start;
	const char	*end;
	char		*word;	

	start = *s;
	while (*start && *start == c)
		start++;
	end = start;
	while (*end && *end != c)
		end++;
	word = ft_substr(start, 0, end - start);
	if (!word)
		return (NULL);
	*s = end;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		i;
	int		word_count;

	if (!s)
		return (NULL);
	word_count = ft_count_words(s, c);
	ptr = (char **) malloc((word_count + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		ptr[i] = ft_save_word(&s, c);
		if (!ptr[i])
		{
			while (i > 0)
				free(ptr[--i]);
			free(ptr);
			return (NULL);
		}
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}
