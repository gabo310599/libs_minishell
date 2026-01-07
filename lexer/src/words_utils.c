/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 18:03:06 by gojeda            #+#    #+#             */
/*   Updated: 2025/12/17 17:47:01 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

// Inicializamos la palabra
void	lexer_start_word(t_lexer *lx)
{
	if (!lx->current_word)
		lx->current_word = token_new(TOKEN_WORD);
}

// Agregamos un caracter a la palabra
void	lexer_add_char(t_lexer *lx, char c)
{
	char	*new;
	char	*old;

	if (!lx->current_seg)
		lexer_start_segment(lx, lx->current_expand);
	old = lx->current_seg->str;
	new = ft_strjoin_char(old, c);
	free(old);
	lx->current_seg->str = new;
}

// Cerramos la palabra
bool	lexer_end_word(t_lexer *lx)
{
	if (!lx->current_word)
		return (true);
	lexer_end_segment(lx);
	if (!lexer_add_token(lx, lx->current_word))
		return (lx->error = 1, false);
	lx->current_word = NULL;
	return (true);
}
