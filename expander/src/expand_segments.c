/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_segments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:05:28 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/19 13:40:13 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"

static bool	is_var_start(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static char	*extract_var(const char *s, size_t *i)
{
	int	start;

	start = *i;
	while (is_var_start(s[*i]))
		(*i)++;
	return (ft_substr(s, start, *i - start));
}

char	*expand_env_var(const char *s, size_t *i, t_env *env)
{
	size_t	start;
	char	*key;
	char	*val;

	start = *i;
	while (ft_isalnum(s[*i]) || s[*i] == '_')
		(*i)++;
	key = ft_substr(s, start, *i - start);
	if (!key)
		return (NULL);
	val = env_get(env, key);
	free(key);
	if (!val)
		return (ft_strdup(""));
	return (val);
}

char	*expand_dollar(const char *s, size_t *i, t_env *env, int last_status)
{
	char	*key;
	char	*val;

	if (s[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(last_status));
	}
	if (!is_var_start(s[*i]))
		return (ft_strdup("$"));
	key = extract_var(s, i);
	val = env_get(env, key);
	free(key);
	return (val);
}

//Expandimos el segmento
char	*expand_segment(t_segment *seg, t_env *env, int last_status)
{
	char		*res;
	char		*tmp;
	size_t		i;

	if (!seg || !seg->str)
		return (ft_strdup(""));
	if (!seg->expand)
		return (ft_strdup(seg->str));
	res = ft_strdup("");
	i = 0;
	while (seg->str[i])
	{
		if (seg->str[i] == '$')
		{
			i++;
			tmp = expand_dollar(seg->str, &i, env, last_status);
			res = ft_str_join_free(res, tmp);
		}
		else
			res = ft_str_join_free(res,
					ft_substr(seg->str, i++, 1));
	}
	return (res);
}
