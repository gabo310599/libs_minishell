/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 02:33:19 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/16 08:53:26 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

//Creamos una redireccion
t_redir	*redir_new(t_redir_type type, t_token *target)
{
	t_redir	*r;

	r = malloc(sizeof(t_redir));
	if (!r)
		return (NULL);
	r->type = type;
	r->target = target;
	r->next = NULL;
	return (r);
}

//Creamos pipeline vacio
t_pipeline	*pipeline_new(void)
{
	t_pipeline	*p;

	p = malloc(sizeof(t_pipeline));
	if (!p)
		return (NULL);
	p->cmds = NULL;
	p->count = 0;
	return (p);
}

//Verificamos si un token es de redireccion
bool	is_redir(t_token_type type)
{
	return (type == TOKEN_REDIR_IN
		|| type == TOKEN_REDIR_OUT
		|| type == TOKEN_APPEND
		|| type == TOKEN_HEREDOC);
}

//Creamos el comando si no existe
bool	start_cmd_if_needed(t_cmd **cmd)
{
	if (*cmd)
		return (true);
	*cmd = cmd_new();
	return (*cmd != NULL);
}