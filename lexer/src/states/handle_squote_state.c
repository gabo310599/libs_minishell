/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_squote_state.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:41:04 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/07 05:00:44 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	handle_in_squote(t_lexer *lx, const char *line,
			size_t *i, int *state)
{
	if (!line[*i])
	{
		lx->error = 1;
		return ;
	}
	if (line[*i] == '\'')
	{
		lexer_end_segment(lx);
		*state = NORMAL;
		(*i)++;
		return ;
	}
	if (!lx->current_seg)
		lexer_start_segment(lx, false);
	lexer_add_char(lx, line[*i]);
	(*i)++;
}
