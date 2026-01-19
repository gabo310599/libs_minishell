/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 13:10:17 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/19 13:25:27 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"

//Expandimos un solo comando
static bool	expand_single_cmd(t_cmd *cmd, t_expand_ctx *ctx)
{
	cmd->argv_expanded = expand_cmd(cmd,
			ctx->env, ctx->last_status);
	if (!cmd->argv_expanded)
		return (false);
	if (!expand_redirs(cmd->redirs, ctx))
		return (false);
	return (true);
}

//Expandimos pipeline
bool	expand_pipeline(t_pipeline *p, t_env *env, int last_status)
{
	t_expand_ctx	ctx;
	int				i;

	if (!p)
		return (true);
	ctx.env = env;
	ctx.last_status = last_status;
	i = 0;
	while (i < p->count)
	{
		if (!expand_single_cmd(p->cmds[i], &ctx))
			return (false);
		i++;
	}
	return (true);
}
