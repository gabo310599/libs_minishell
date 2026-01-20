/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 13:03:53 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/20 15:23:35 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"

// Expandir UNA redirección
static bool	expand_single_redir(t_redir *r, t_expand_ctx *ctx)
{
	char	*expanded;

	if (r->type == REDIR_HEREDOC)
	{
		expanded = token_to_literal(r->target);
		if (!expanded)
			return (false);
		r->target->value = expanded;
		return (true);
	}
	expanded = expand_token(r->target, ctx->env, ctx->last_status);
	if (!expanded)
		return (false);
	free(r->target->value);
	r->target->value = expanded;
	return (true);
}

// Expandimos todas las redirecciones
bool	expand_redirs(t_redir *redirs, t_expand_ctx *ctx)
{
	t_redir	*r;

	r = redirs;
	while (r)
	{
		if (!expand_single_redir(r, ctx))
			return (false);
		r = r->next;
	}
	return (true);
}
