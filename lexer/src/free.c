/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 15:10:47 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/07 10:16:42 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

// Liberamos los segmentos
static void	free_segments(t_segment *seg)
{
	t_segment	*tmp;

	while (seg)
	{
		tmp = seg->next;
		free(seg->str);
		free(seg);
		seg = tmp;
	}
}

// Liberamos todos los tokens del lexer
void	lexer_destroy(t_lexer *lex)
{
	t_token	*tmp;

	if (!lex)
		return ;
	while (lex->head)
	{
		tmp = lex->head->next;
		if (lex->head->segments)
			free_segments(lex->head->segments);
		free(lex->head);
		lex->head = tmp;
	}
	free(lex);
}
