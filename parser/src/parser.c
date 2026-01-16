/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 07:49:21 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/16 09:17:28 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

//Funcion principal de parseo
t_pipeline	*parse_tokens(t_token *tokens)
{
	t_pipeline		*p;
	t_cmd			*cmd;
	t_token			*tok;
	t_token_type	prev_type;

	p = pipeline_new();
	if (!p)
		return (NULL);
	cmd = NULL;
	tok = tokens;
	prev_type = TOKEN_EOF;
	while (tok && tok->type != TOKEN_EOF)
	{
		if (!dispatch_token(p, &cmd, &tok))
			return (free_all(p, cmd), NULL);
		prev_type = tok->type;
		tok = tok->next;
	}
	if (prev_type == TOKEN_PIPE)
		return (free_all(p, cmd), NULL);
	if (cmd && !finalize_cmd(p, &cmd))
		return (free_all(p, cmd), NULL);
	return (p);
}
