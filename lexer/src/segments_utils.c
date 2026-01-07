/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segments_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 17:32:29 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/07 04:53:41 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

//Inicializamos un segmento
void	lexer_start_segment(t_lexer *lx, bool expand)
{
	if (lx->current_seg)
		return ;
	lx->current_expand = expand;
	lx->current_seg = segment_new(ft_strdup(""), expand);
	if (!lx->current_seg)
		lx->error = 1;
}

//Cerramos el segmento
void	lexer_end_segment(t_lexer *lx)
{
	if (!lx->current_seg)
		return ;
	if (!lx->current_word)
		lx->current_word = token_new(TOKEN_WORD);
	token_add_segment(lx->current_word, lx->current_seg);
	lx->current_seg = NULL;
}
