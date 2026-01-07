/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dquote_state.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:44:00 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/07 04:59:48 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static void	escapes_dquote(char next, t_lexer *lx, size_t *i)
{
	if (!next)
	{
		lexer_add_char(lx, '\\');
		(*i)++;
		return ;
	}
	if (next == '"' || next == '\\' || next == '$')
	{
		lexer_add_char(lx, next);
		*i += 2;
		return ;
	}
	lexer_add_char(lx, '\\');
	(*i)++;
	return ;
}

void	handle_in_dquote(t_lexer *lx, const char *line,
			size_t *i, int *state)
{
	if (!line[*i])
	{
		lx->error = 1;
		return ;
	}
	if (line[*i] == '"')
	{
		lexer_end_segment(lx);
		*state = NORMAL;
		(*i)++;
		return ;
	}
	if (line[*i] == '\\')
	{
		escapes_dquote(line[*i + 1], lx, i);
		return ;
	}
	if (!lx->current_seg)
		lexer_start_segment(lx, true);
	lexer_add_char(lx, line[*i]);
	(*i)++;
}
