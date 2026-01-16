/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 08:18:21 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/16 08:55:55 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

//Traducimos los token a un redir type
static t_redir_type	token_to_redir_type(t_token_type type)
{
	if (type == TOKEN_REDIR_IN)
		return (REDIR_IN);
	if (type == TOKEN_REDIR_OUT)
		return (REDIR_OUT);
	if (type == TOKEN_APPEND)
		return (REDIR_APPEND);
	if (type == TOKEN_HEREDOC)
		return (REDIR_HEREDOC);
	return (-1);
}


//Handler para WORD
bool	parse_word(t_pipeline *p, t_cmd **cmd, t_token *tok)
{
	(void)p;
	if (!start_cmd_if_needed(cmd))
		return (false);
	return (cmd_add_arg(*cmd, tok));
}

//Handler para pipe
bool	parse_pipe(t_pipeline *p, t_cmd **cmd)
{
	return (finalize_cmd(p, cmd));
}

//Handler para redirecciones
bool	parse_redir(t_cmd *cmd, t_token **tok)
{
	t_redir	*r;

	if (!cmd || !(*tok)->next || (*tok)->next->type != TOKEN_WORD)
		return (false);
	r = redir_new(token_to_redir_type((*tok)->type), (*tok)->next);
	if (!r)
		return (false);
	if (!cmd_add_redir(cmd, r))
		return (false);
	*tok = (*tok)->next;
	return (true);
}

//Control de handlers
bool	dispatch_token(t_pipeline *p, t_cmd **cmd, t_token **tok)
{
	if ((*tok)->type == TOKEN_WORD)
		return (parse_word(p, cmd, *tok));
	if ((*tok)->type == TOKEN_PIPE)
		return (parse_pipe(p, cmd));
	if (is_redir((*tok)->type))
		return (parse_redir(*cmd, tok));
	return (false);
}



