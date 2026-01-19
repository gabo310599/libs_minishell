/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:57:44 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/19 13:57:39 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"

void	free_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
}

char	*token_to_literal(t_token *tok)
{
	t_segment	*seg;
	char		*res;
	char		*tmp;

	res = ft_strdup("");
	if (!res)
		return (NULL);
	seg = tok->segments;
	while (seg)
	{
		tmp = ft_strjoin(res, seg->str);
		free(res);
		if (!tmp)
			return (NULL);
		res = tmp;
		seg = seg->next;
	}
	return (res);
}
