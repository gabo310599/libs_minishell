/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_normal_state.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:27:24 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/07 05:17:21 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static void	normal_operator(t_lexer *lx, const char *line, size_t *i)
{
	t_token_type	type;
	t_token			*tok;

	lexer_end_word(lx);
	type = identify_operator(&line[*i]);
	tok = token_new(type);
	lexer_add_token(lx, tok);
	*i += operator_length(&line[*i]);
}

static void	normal_in_squote(t_lexer *lx, int *state, size_t *i)
{
	lexer_start_word(lx);
	if (lx->current_seg)
		lexer_end_segment(lx);
	if (!lx->current_seg)
		lexer_start_segment(lx, false);
	lx->current_expand = false;
	*state = IN_SQUOTE;
	(*i)++;
}

static void	normal_in_dquote(t_lexer *lx, int *state, size_t *i)
{
	lexer_start_word(lx);
	if (lx->current_seg)
		lexer_end_segment(lx);
	if (!lx->current_seg)
		lexer_start_segment(lx, true);
	lx->current_expand = true;
	*state = IN_DQUOTE;
	(*i)++;
}

static void	normal_text(t_lexer *lx, const char *line, size_t *i)
{
	if (!lx->current_word)
		lexer_start_word(lx);
	if (!lx->current_seg)
		lexer_start_segment(lx, true);
	lexer_add_char(lx, line[*i]);
}

void	handle_normal(t_lexer *lx, const char *line,
			size_t *i, int *state)
{
	if (is_operator_char(line[*i]))
	{
		normal_operator(lx, line, i);
		return ;
	}
	if (line[*i] == '\'')
	{
		normal_in_squote(lx, state, i);
		return ;
	}
	if (line[*i] == '"')
	{
		normal_in_dquote(lx, state, i);
		return ;
	}
	if (line[*i] == ' ' || line[*i] == '\t')
	{
		lexer_end_word(lx);
		(*i)++;
		return ;
	}
	normal_text(lx, line, i);
	(*i)++;
}
