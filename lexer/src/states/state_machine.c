/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 15:31:04 by gojeda            #+#    #+#             */
/*   Updated: 2025/11/30 20:26:10 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static bool	finalize_lexer(t_lexer	*lx)
{
	t_token	*eof;

	lexer_end_word(lx);
	if (lx->error)
	{
		lexer_destroy(lx);
		return (true);
	}
	eof = token_new(TOKEN_EOF);
	if (!eof)
	{
		lexer_destroy(lx);
		return (true);
	}
	if (!lexer_add_token(lx, eof))
	{
		free(eof);
		lexer_destroy(lx);
		return (true);
	}
	return (false);
}

t_lexer	*lexer_tokenize(const char *line)
{
	t_lexer	*lx;
	size_t	i;
	int		state;

	lx = lexer_create();
	if (!lx)
		return (NULL);
	i = 0;
	state = NORMAL;
	while (line[i])
	{
		if (state == NORMAL)
			handle_normal(lx, line, &i, &state);
		else if (state == IN_SQUOTE)
			handle_in_squote(lx, line, &i, &state);
		else if (state == IN_DQUOTE)
			handle_in_dquote(lx, line, &i, &state);
		if (lx->error)
			break ;
	}
	if (finalize_lexer(lx))
		return (NULL);
	return (lx);
}
