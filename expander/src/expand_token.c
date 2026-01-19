/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:52:30 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/19 13:41:29 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"

static char	**alloc_argv(int argc)
{
	char	**argv;

	argv = malloc(sizeof(char *) * (argc + 1));
	if (!argv)
		return (NULL);
	argv[argc] = NULL;
	return (argv);
}

static bool	expand_argv_token(char **argv, int i,
	t_token *tok,
	t_expand_ctx *ctx)
{
	argv[i] = expand_token(tok, ctx->env, ctx->last_status);
	if (!argv[i])
		return (false);
	return (true);
}

//Expandimos los tokens
char	*expand_token(t_token *tok, t_env *env, int last_status)
{
	t_segment	*seg;
	char		*res;
	char		*tmp;

	if (!tok || tok->type != TOKEN_WORD)
		return (NULL);
	res = ft_strdup("");
	if (!res)
		return (NULL);
	seg = tok->segments;
	while (seg)
	{
		tmp = expand_segment(seg, env, last_status);
		if (!tmp)
			return (free(res), NULL);
		res = ft_str_join_free(res, tmp);
		seg = seg->next;
	}
	return (res);
}

//Expandimos cmd
char	**expand_cmd(t_cmd *cmd, t_env *env, int last_status)
{
	t_expand_ctx	ctx;
	char			**argv;
	int				i;

	if (!cmd)
		return (NULL);
	ctx.env = env;
	ctx.last_status = last_status;
	argv = alloc_argv(cmd->argc);
	if (!argv)
		return (NULL);
	i = 0;
	while (i < cmd->argc)
	{
		if (!expand_argv_token(argv, i, cmd->argv[i], &ctx))
			return (free_argv(argv), NULL);
		i++;
	}
	return (argv);
}
